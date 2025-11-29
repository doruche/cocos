#include "vsfs.h"
#include <libs/prelude.h>
#include <libs/path.h>

extern struct vsfs_super vsfs_super;

result_t
vsfs_lookup(u16 dir_ino, const char* name, u16 *out_ino) {
    struct vsfs_inode dir_inode;
    unwrap_err(vsfs_read_inode(dir_ino, &dir_inode));

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
        if (bytes_read != sizeof(dirent)) {
            return -ERR_IO;
        }
        if (strcmp(dirent.name, name) == 0) {
            *out_ino = dirent.ino;
            return OK;
        }
        offset += sizeof(dirent);
    }

    return -ERR_NOT_FOUND;
}

result_t
vsfs_create(u16 dir_ino, const char* name, u32 mode, u16 *out_ino) {
    u16 existing_ino;
    result_t ret = vsfs_lookup(dir_ino, name, &existing_ino);
    if (ret == OK) {
        return -ERR_EXIST;
    } else if (ret != -ERR_NOT_FOUND) {
        return ret;
    }

    u16 new_ino;
    unwrap_err(vsfs_alloc_inode(&new_ino));

    struct vsfs_inode new_inode = {
        .in_use = true,
        .size = 0,
        .nlinks = 1,
        .mode = mode
    };

    /* for mkdir */
    if (S_ISDIR(mode)) {
        new_inode.nlinks = 2;
        new_inode.size = 2 * sizeof(struct vsfs_dirent);

        struct vsfs_dirent entries[] = {
            { .name = ".", .ino = new_ino },
            { .name = "..", .ino = dir_ino }
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
    }
    unwrap_err(vsfs_write_inode(new_ino, &new_inode));

    struct vsfs_dirent dirent;
    strncpy(dirent.name, name, sizeof(dirent.name));
    dirent.name[sizeof(dirent.name) - 1] = '\0';
    dirent.ino = new_ino;

    struct vsfs_inode dir_inode;
    unwrap_err(vsfs_read_inode(dir_ino, &dir_inode));

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

    dir_inode.size += sizeof(dirent);

    if (S_ISDIR(mode)) {
        dir_inode.nlinks += 1;
    }

    unwrap_err(vsfs_write_inode(dir_ino, &dir_inode));

    *out_ino = new_ino;
    return OK;
}

result_t
vsfs_readdir(u16 dir_ino, usize offset, struct vsfs_dirent *out) {
    struct vsfs_inode dir_inode;
    unwrap_err(vsfs_read_inode(dir_ino, &dir_inode));

    if (offset >= dir_inode.size) {
        return -ERR_OUT_OF_BOUNDS;
    }

    usize bytes_read = 0;
    unwrap_err(vsfs_read(
        dir_ino,
        out,
        sizeof(struct vsfs_dirent),
        offset,
        &bytes_read
    ));
    if (bytes_read != sizeof(struct vsfs_dirent)) {
        return -ERR_IO;
    }

    return OK;
}

result_t
vsfs_resolve_path(char* path, u16 *out_ino) {
    path_canonicalize(path, path);
    if (strcmp(path, "/") == 0) {
        *out_ino = 0;
        return OK;
    }
 
    const char* cur = path;
    char name_buf[30];
    u16 dir_ino = VSFS_ROOT_INO;
    u16 nxt_ino;
    while (*cur != '\0') {    
        cur = path_skipcomp(cur, name_buf);
        if (name_buf[0] == '\0') {
            break;
        }
        result_t ret = vsfs_lookup(dir_ino, name_buf, &nxt_ino);
        if (is_err(ret)) {
            return ret;
        }
        dir_ino = nxt_ino;
    }
    *out_ino = dir_ino;
    return OK;
}
