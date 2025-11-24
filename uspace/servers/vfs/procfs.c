#include "procfs.h"
#include "file.h"
#include <libs/prelude.h>
#include <libs/list.h>

static list_head(processes);

static result_t
proc_get(
    pid_t pid,
    struct process_t** out_proc,
    bool alloc
) {
    list_foreach(iter, &processes) {
        struct process_t* proc = list_entry(iter, struct process_t, node);
        if (proc->pid == pid) {
            *out_proc = proc;
            return OK;
        }
    }
    if (!alloc) {
        return -ERR_NOENT;
    }
    struct process_t* proc = unwrap_null(
        malloc(sizeof(struct process_t))
    );
    proc->pid = pid;
    for (usize i = 0; i < MAX_FDS_PER_PROC; i++) {
        proc->files[i].vfs_file = NULL;
        proc->files[i].flags = 0;
        proc->files[i].offset = 0;
    }
    list_push_back(&processes, &proc->node);
    *out_proc = proc;
    return OK;
}

result_t
proc_open(
    pid_t pid,
    const char* path,
    vfs_open_flags_t flags,
    u64* out_fd
) {
    struct process_t* proc = NULL;
    unwrap_err(proc_get(pid, &proc, true));
    for (usize fd = 0; fd < MAX_FDS_PER_PROC; fd++) {
        if (proc->files[fd].vfs_file == NULL) {
            struct fs_file_t* vfs_file = NULL;
            result_t ret = file_get(
                path, 
                (flags & O_CREATE) != 0,
                &vfs_file
            );
            if (is_err(ret)) {
                pr_warn("procfs: open failed for pid %d path %s err code %s\n",
                    pid, path, strerr(ret)
                );
                return ret;
            }
            proc->files[fd].vfs_file = vfs_file;
            proc->files[fd].flags = flags;
            *out_fd = fd;
            return OK;
        }
    }
    return -ERR_NOSPC;
}

static result_t
proc_release_fd(
    pid_t pid,
    u64 fd,
    bool unlink
) {
    struct process_t* proc = NULL;
    result_t ret = proc_get(pid, &proc, false);
    if (is_err(ret)) {
        pr_warn("procfs: release failed for pid %d fd %ld: proc not found\n",
            pid, fd
        );
        return ret;
    }
    if (fd < MAX_FDS_PER_PROC) {
        struct proc_file_t* pfile = &proc->files[fd];
        if (pfile->vfs_file != NULL) {
            unwrap_err(file_put(pfile->vfs_file, unlink));
            pfile->vfs_file = NULL;
            pfile->flags = 0;
            pfile->offset = 0;
            return OK;
        }
    }

    pr_warn("procfs: release failed for pid %d fd %ld: invalid fd\n",
        pid, fd
    );
    return -ERR_NOENT;
}

void
proc_exit(pid_t pid) {
    struct process_t* proc = NULL;
    result_t ret = proc_get(pid, &proc, false);
    if (is_err(ret)) {
        /*
         * this can be normal, e.g. the process never opened any file
         * buf it may also indicate a bug in proc_close handling...
         * let's leave it as is for now.
         */
        pr_info("procfs: proc_exit for pid %d: proc not found, nothing to do\n",
            pid
        );
        return;
    }
    for (usize fd = 0; fd < MAX_FDS_PER_PROC; fd++) {
        struct proc_file_t* pfile = &proc->files[fd];
        if (pfile->vfs_file != NULL) {
            unwrap_err(file_put(pfile->vfs_file, false, false));
        }
    }
    list_remove(&proc->node);
    free(proc);
    pr_info("procfs: proc_exit for pid %d: cleaned up\n", pid);
}

result_t
proc_close(pid_t pid, u64 fd) {
    return proc_release_fd(pid, fd, false);
}

result_t
proc_unlink(pid_t pid, u64 fd) {
    return proc_release_fd(pid, fd, true);
}

result_t
proc_read(
    pid_t pid,
    u64 fd,
    u8* buf,
    u64 size,
    u64* out_size
) {
    struct process_t* proc = NULL;
    result_t ret = proc_get(pid, &proc, false);
    if (is_err(ret)) {
        pr_warn("procfs: read failed for pid %d fd %ld: proc not found\n",
            pid, fd
        );
        return ret;
    }
    if (fd < MAX_FDS_PER_PROC) {
        struct proc_file_t* pfile = &proc->files[fd];
        if (pfile->vfs_file != NULL) {
            usize offset = pfile->offset;
            if (!(pfile->flags & O_RDONLY ||
                  pfile->flags & O_RDWR)) {
                pr_warn("procfs: read failed for pid %d fd %ld: file not opened for reading\n",
                    pid, fd
                );
                return -ERR_PERM;
            }
            ret = file_read(
                pfile->vfs_file,
                buf,
                size,
                offset,
                out_size
            );
            if (is_err(ret)) {
                pr_warn("procfs: read failed for pid %d fd %ld: file read error %s\n",
                    pid, fd, strerr(ret)
                );
                return ret;
            }
            pfile->offset += *out_size;
            return OK;
        }
    }

    pr_warn("procfs: read failed for pid %d fd %ld: invalid fd\n",
        pid, fd
    );
    return -ERR_NOENT;
}

result_t
proc_write(
    pid_t pid,
    u64 fd,
    const u8* buf,
    u64 size,
    u64* out_size
) {
    struct process_t* proc = NULL;
    result_t ret = proc_get(pid, &proc, false);
    if (is_err(ret)) {
        pr_warn("procfs: write failed for pid %d fd %ld: proc not found\n",
            pid, fd
        );
        return ret;
    }
    if (fd < MAX_FDS_PER_PROC) {
        struct proc_file_t* pfile = &proc->files[fd];
        if (pfile->vfs_file != NULL) {
            if (!(pfile->flags & O_WRONLY ||
                  pfile->flags & O_RDWR)) {
                pr_warn("procfs: write failed for pid %d fd %ld: file not opened for writing\n",
                    pid, fd
                );
                return -ERR_PERM;
            }
            ret = file_write(
                pfile->vfs_file,
                buf,
                size,
                pfile->offset,
                out_size
            );
            if (is_err(ret)) {
                pr_warn("procfs: write failed for pid %d fd %ld: file write error %s\n",
                    pid, fd, strerr(ret)
                );
                return ret;
            }
            pfile->offset += *out_size;
            return OK;
        }
    }

    pr_warn("procfs: write failed for pid %d fd %ld: invalid fd\n",
        pid, fd
    );
    return -ERR_NOENT;
}
