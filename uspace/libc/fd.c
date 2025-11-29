#include <libs/prelude.h>
#include <libs/path.h>
#include <uspace/servers/fs.h>
#include <uspace/fd.h>

static fd_t open_fds[PER_PROC_OFILES_MAX];
static char cwd[PATH_MAX_LEN];

void
fd_init(void) {
    /*
     * not "/" ? cz we don't have a fs mounted at the beginning.
     * each process manages its own name space. so let itself
     * to mount a preferred rootfs to "/" later...
     */
    strncpy(cwd, "", PATH_MAX_LEN);
    for (usize i = 0; i < PER_PROC_OFILES_MAX; i++) {
        open_fds[i].fs_handle = HANDLE_INVALID;
        open_fds[i].id = i;
        open_fds[i].in_use = false;
    }
}

static fd_t*
fd_alloc(void) {
    for (usize i = 0; i < PER_PROC_OFILES_MAX; i++) {
        if (!open_fds[i].in_use) {
            open_fds[i].in_use = true;
            return &open_fds[i];
        }
    }
    return NULL;
}

static void
fmt_path(const char* path, char* out_buf) {
    if (path_is_absolute(path)) {
        strncpy(out_buf, path, PATH_MAX_LEN);
    } else {
        snprintf(out_buf, PATH_MAX_LEN, "%s/%s", cwd, path);
    }
    path_canonicalize(out_buf, out_buf);
}

result_t
open(const char* path, u64 flags, u64* out) {
    tid_t owner;
    char buf[PATH_MAX_LEN];
    char rpath[PATH_MAX_LEN];

    fmt_path(path, buf);
    result_t ret = ns_resolve(
        buf,
        &owner,
        rpath
    );
    if (is_err(ret)) {
        return ret;
    }
    handle_t fs_handle;
    if (flags & O_CREATE) {
        ret = fs_create(owner, rpath, flags & S_IFMT, &fs_handle);
    } else {
        ret = fs_get(owner, rpath, &fs_handle);
    }
    if (is_err(ret)) {
        return ret;
    }
    fd_t* fd = fd_alloc();
    if (fd == NULL) {
        return -ERR_NOMEM;
    }
    
    fd->fs = owner;
    fd->fs_handle = fs_handle;
    fd->offset = 0;
    fd->flags = flags & (O_RDONLY | O_WRONLY | O_RDWR);
    *out = fd->id;
    return OK;
}

result_t
close(u64 fd) {
    if (fd >= PER_PROC_OFILES_MAX) {
        return -ERR_INVAL;
    }
    if (!open_fds[fd].in_use) {
        return -ERR_INVAL;
    }
    open_fds[fd].fs_handle = HANDLE_INVALID;
    open_fds[fd].in_use = false;
    return OK;
}

result_t
read(u64 fd, void* buffer, u64 size, usize* bytes_read) {
    if (fd >= PER_PROC_OFILES_MAX) {
        return -ERR_INVAL;
    }
    if (!open_fds[fd].in_use) {
        return -ERR_INVAL;
    }
    fd_t* fdesc = &open_fds[fd];
    if (fdesc->flags != O_RDONLY &&
        fdesc->flags != O_RDWR) {
        return -ERR_PERM;
    }
    usize tmp = 0;
    result_t ret = fs_read(
        fdesc->fs,
        fdesc->fs_handle,
        (u8*)buffer,
        size,
        fdesc->offset,
        &tmp
    );    
    if (is_err(ret)) {
        return ret;
    }
    fdesc->offset += tmp;
    if (bytes_read != NULL) {
        *bytes_read = tmp;
    }
    return OK;
}

result_t
readdir(u64 fd, struct dirent_t* out, usize* next_offset) {
    if (fd >= PER_PROC_OFILES_MAX) {
        return -ERR_INVAL;
    }
    if (!open_fds[fd].in_use) {
        return -ERR_INVAL;
    }
    fd_t* fdesc = &open_fds[fd];
    usize tmp_next_offset = 0;
    result_t ret = fs_readdir(
        fdesc->fs,
        fdesc->fs_handle,
        fdesc->offset,
        out,
        &tmp_next_offset
    );
    if (is_err(ret)) {
        return ret;
    }
    fdesc->offset = tmp_next_offset;
    if (next_offset != NULL) {
        *next_offset = tmp_next_offset;
    }
    return OK;
}

result_t
write(u64 fd, const void* buffer, u64 size, usize* bytes_written) {
    if (fd >= PER_PROC_OFILES_MAX) {
        return -ERR_INVAL;
    }
    if (!open_fds[fd].in_use) {
        return -ERR_INVAL;
    }
    fd_t* fdesc = &open_fds[fd];
    if (fdesc->flags != O_WRONLY &&
        fdesc->flags != O_RDWR) {
        return -ERR_PERM;
    }
    usize tmp = 0;
    result_t ret = fs_write(
        fdesc->fs,
        fdesc->fs_handle,
        (const u8*)buffer,
        size,
        fdesc->offset,
        &tmp
    );
    if (is_err(ret)) {
        return ret;
    }
    fdesc->offset += tmp;
    if (bytes_written != NULL) {
        *bytes_written = tmp;
    }
    return OK;
}

result_t
lseek(u64 fd, isize offset, seek_whence_t whence) {
    if (fd >= PER_PROC_OFILES_MAX) {
        return -ERR_INVAL;
    }
    if (!open_fds[fd].in_use) {
        return -ERR_INVAL;
    }
    fd_t* fdesc = &open_fds[fd];
    stat_t st;
    result_t ret = fs_fstat(fdesc->fs, fdesc->fs_handle, &st);
    if (is_err(ret)) {
        return ret;
    }
    usize new_offset;
    switch (whence) {
        case SEEK_SET: {
            if (offset < 0 || offset >= st.size) {
                pr_info("lseek: SEEK_SET invalid offset %ld for fd %ld with size %ld",
                    offset, fd, st.size);
                return -ERR_INVAL;
            }
            new_offset = (usize)offset;
            break;
        }
        case SEEK_CUR: {
            isize temp = (isize)fdesc->offset + offset;
            if (temp < 0 || (usize)temp >= st.size) {
                return -ERR_INVAL;
            }
            new_offset = (usize)temp;
            break;
        }
        case SEEK_END: {
            isize temp = (isize)st.size + offset;
            if (temp < 0 || (usize)temp >= st.size) {
                return -ERR_INVAL;
            }
            new_offset = (usize)temp;
            break;
        }
        default: {
            return -ERR_INVAL;
        }
    }
    fdesc->offset = new_offset;
    return OK;
}

result_t
stat(const char* path, stat_t* out) {
    tid_t owner;
    char buf[PATH_MAX_LEN];
    char rpath[PATH_MAX_LEN];
    fmt_path(path, buf);

    result_t ret = ns_resolve(
        buf,
        &owner,
        rpath
    );
    if (is_err(ret)) {
        return ret;
    }
    ret = fs_stat(owner, rpath, out);
    return ret;
}

result_t
fstat(u64 fd, stat_t* out) {
    if (fd >= PER_PROC_OFILES_MAX) {
        return -ERR_INVAL;
    }
    if (!open_fds[fd].in_use) {
        return -ERR_INVAL;
    }
    fd_t* fdesc = &open_fds[fd];
    result_t ret = fs_fstat(
        fdesc->fs,
        fdesc->fs_handle,
        out
    );
    return ret;
}

const char*
pwd(void) {
    return (const char*)cwd;
}

result_t
chdir(const char* path)  {
    char buf[PATH_MAX_LEN];
    fmt_path(path, buf);

    tid_t owner; /* this should be a fs server */
    char rpath[PATH_MAX_LEN];
    result_t ret = ns_resolve(
        buf,
        &owner,
        rpath
    );
    if (is_err(ret)) {
        return ret;
    }

    stat_t st;
    ret = fs_stat(owner, rpath, &st);
    if (is_err(ret)) {
        pr_info("chdir: fs_stat failed for path %s: %s",
            buf, strerr(ret));
        return ret;
    }
    if (!S_ISDIR(st.mode)) {
        pr_info("chdir: path %s is not a directory", buf);
        return -ERR_INVAL;
    }
    strncpy(cwd, buf, PATH_MAX_LEN);
    return OK;
}
