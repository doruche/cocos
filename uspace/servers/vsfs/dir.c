#include "vsfs.h"
#include <libs/prelude.h>
#include <libs/path.h>

extern struct vsfs_super vsfs_super;

result_t
vsfs_lookup(u16 dir_ino, const char* name, struct vsfs_dirent *out) {
    struct vsfs_inode dir_inode;
    result_t ret = vsfs_read_inode(dir_ino, &dir_inode);
    if (is_err(ret)) {
        return ret;
    }

    usize offset = 0;
    while (offset < dir_inode.size) {
        usize bytes_read = 0;
        struct vsfs_dirent dirent;
        unwrap_err(vsfs_read(
            dir_ino,
            &dirent,
            sizeof(dirent),
            offset,
            &bytes_read
        ));
        pr_info("vsfs_lookup: checking dir ino %d at offset %ld: name=%s, ino=%d",
            dir_ino,
            offset,
            dirent.name,
            dirent.ino
        );
        if (bytes_read != sizeof(dirent)) {
            return -ERR_IO;
        }
        if (strcmp(dirent.name, name) == 0) {
            *out = dirent;
            return OK;
        }
        offset += sizeof(dirent);
    }

    return -ERR_NOT_FOUND;
}

result_t
vsfs_create(u16 dir_ino, const char* name, u32 mode, u16 *out_ino) {
    mode = mode & S_IFMT;
    if (mode != S_IFREG && mode != S_IFDIR) {
        return -ERR_NOT_SUPPORTED;
    }

    result_t ret = vsfs_lookup(dir_ino, name, &(struct vsfs_dirent){0});
    if (ret == OK) {
        return -ERR_EXIST;
    } else if (ret != -ERR_NOT_FOUND) {
        return ret;
    }

    u16 new_ino;
    ret = vsfs_alloc_inode(&new_ino);
    if (is_err(ret)) {
        return ret;
    }

    struct vsfs_inode new_inode = {
        .in_use = true,
        .size = 0,
        .nlinks = 1,
        .mode = mode
    };

    struct vsfs_inode dir_inode;
    unwrap_err(vsfs_read_inode(dir_ino, &dir_inode));

    /* for mkdir */
    if (S_ISDIR(mode)) {
        new_inode.nlinks = 2;
        new_inode.size = 2 * sizeof(struct vsfs_dirent);

        struct vsfs_dirent entries[] = {
            { .name = ".", .ino = new_ino, .mode = S_IFDIR },
            { .name = "..", .ino = dir_ino, .mode = S_IFDIR }
        };
        usize bytes_written = 0;
        ret = vsfs_write(
            new_ino,
            entries,
            sizeof(entries),
            0,
            &bytes_written
        );
        if (is_err(ret) || bytes_written != sizeof(entries)) {
            unwrap_err(vsfs_free_inode(new_ino));
            return is_err(ret) ? ret : -ERR_IO;
        }
        dir_inode.nlinks += 1;
        unwrap_err(vsfs_write_inode(dir_ino, &dir_inode));
    }
    unwrap_err(vsfs_write_inode(new_ino, &new_inode));

    struct vsfs_dirent dirent;
    strncpy(dirent.name, name, sizeof(dirent.name));
    dirent.name[sizeof(dirent.name) - 1] = '\0';
    dirent.ino = new_ino;
    dirent.mode = mode;

    pr_info("vsfs_create: created %s with ino %d in dir ino %d",
        S_ISDIR(mode) ? "directory" : "file",
        new_ino,
        dir_ino
    );

    usize bytes_written = 0;
    unwrap_err(vsfs_write(
        dir_ino,
        &dirent,
        sizeof(dirent),
        dir_inode.size,
        &bytes_written
    ));
    if (bytes_written != sizeof(dirent)) {
        return -ERR_IO;
    }

    *out_ino = new_ino;
    return OK;
}

result_t
vsfs_readdir(u16 dir_ino, usize offset, struct vsfs_dirent *out, usize *next_offset) {
    struct vsfs_inode dir_inode;
    result_t ret = vsfs_read_inode(dir_ino, &dir_inode);
    if (is_err(ret)) {
        return ret;
    }

    if (!S_ISDIR(dir_inode.mode)) {
        return -ERR_INVAL;
    }

    if (offset * sizeof(struct vsfs_dirent) >= dir_inode.size) {
        return -ERR_OUT_OF_BOUNDS;
    }

    usize bytes_read = 0;
    struct vsfs_dirent dirent;
    
    unwrap_err(vsfs_read(
        dir_ino,
        &dirent,
        sizeof(dirent),
        offset * sizeof(struct vsfs_dirent),
        &bytes_read
    ));

    if (bytes_read != sizeof(dirent)) {
        return -ERR_IO;
    }
    *out = dirent;
    if ((offset + 1) * sizeof(struct vsfs_dirent) >= dir_inode.size) {
        *next_offset = 0; /* loop back */
    } else {
        *next_offset = offset + 1;
    }
    return OK;
}

result_t
vsfs_resolve_path(char* path, struct vsfs_dirent *out) {
    if (!path_is_absolute(path)) {
        return -ERR_INVAL;
    }
    path_canonicalize(path, path);
    if (strcmp(path, "/") == 0) {
        *out = (struct vsfs_dirent){
            .ino = VSFS_ROOT_INO,
            .name = "/",
            .mode = S_IFDIR,
        };
        return OK;
    }
 
    const char* cur = path;
    char name_buf[30];
    u16 dir_ino = VSFS_ROOT_INO;
    struct vsfs_dirent nxt;
    while (*cur != '\0') {    
        cur = path_skipcomp(cur, name_buf);
        pr_info("vsfs_resolve_path: looking up component '%s' in dir ino %d",
            name_buf,
            dir_ino);
        result_t ret = vsfs_lookup(dir_ino, name_buf, &nxt);
        if (is_err(ret)) {
            return ret;
        }
        if (*cur == '\0') {
            /* reached target */
            break;   
        } else {
            if (!S_ISDIR(nxt.mode)) {
                return -ERR_FMT;
            }
            dir_ino = nxt.ino;
        }
    }
    *out = nxt;
    return OK;
}
