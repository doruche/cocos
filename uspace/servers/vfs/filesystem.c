#include "filesystem.h"
#include <libs/prelude.h>
#include <libs/list.h>
#include <uspace/ipc.h>
#include <uspace/task.h>

static list_head(filesystems);

static result_t
vfs_fs_get(pid_t pid, struct filesystem_t** out_fs) {
    list_foreach(iter, &filesystems) {
        struct filesystem_t* fs = list_entry(iter, struct filesystem_t, node);
        if (fs->fs == pid) {
            *out_fs = fs;
            return 0;
        }
    }
    return -ERR_NOENT;
}

/* currently we do not demand that the directory exists */
result_t
vfs_mount(
    pid_t fs,
    const char* mountp
) {
    if (mountp[0] != '/') {
        return -ERR_INVAL;
    }

    list_foreach(iter, &filesystems) {
        struct filesystem_t* fss = list_entry(iter, struct filesystem_t, node);
        if (strcmp(fss->mountp, mountp) == 0) {
            return -ERR_EXIST;
        }
    }

    struct filesystem_t* fss = unwrap_null(
        malloc(sizeof(struct filesystem_t))
    );
    fss->fs = fs;
    strncpy(fss->mountp, mountp, PATH_MAX_LEN);
    
    result_t ret = proc_watch(fs);
    if (is_err(ret)) {
        pr_warn("vfs: proc_watch failed for tid %ld: %s",
            fs,
            strerr(ret));
        free(fss);
        return ret;
    }

    list_push_back(&filesystems, &fss->node);
    return OK;
}

void
vfs_umount(pid_t fs) {
    list_foreach_safe(iter, &filesystems, next) {
        struct filesystem_t* fss = list_entry(iter, struct filesystem_t, node);
        if (fss->fs == fs) {
            list_remove(&fss->node);
            free(fss);
            return;
        }
    }
    pr_warn("vfs_umount: fs %ld not found", fs);
}

static usize
mountp_match(const char* path, const char* mountp) {
    usize len = strlen(mountp);
    if (strncmp(path, mountp, len) != 0) {
        return 0;
    }

    if (len == PATH_MAX_LEN) {
        return 0;
    }

    if (path[len] != '/' && path[len] != '\0') {
        return 0;
    }

    if (len == 1 && mountp[0] == '/') {
        return 1;
    }

    return len;
}

result_t
vfs_resolve(
    const char* path,
    struct filesystem_t** out_fs,
    char* out_rpath
) {
    struct filesystem_t* target = NULL;
    usize max_matched = 0;
    list_foreach(iter, &filesystems) {
        struct filesystem_t* fs = list_entry(iter, struct filesystem_t, node);
        usize matched = mountp_match(path, fs->mountp);
        if (matched > max_matched) {
            max_matched = matched;
            target = fs;
        }
    }
    if (target == NULL) {
        return -ERR_NOENT;
    }
    if (out_fs != NULL) {
        *out_fs = target;
    }
    if (out_rpath != NULL) {
        const char* rpath = path + max_matched;
        if (max_matched == 1 && target->mountp[0] == '/') {
            /* root mount point, use full path */
            strncpy(out_rpath, path, PATH_MAX_LEN);
        } else if (rpath[0] == '\0') {
            out_rpath[0] = '/';
            out_rpath[1] = '\0';
        } else if (rpath[0] != '/') {
            out_rpath[0] = '/';
            strncpy(
                out_rpath + 1,
                rpath,
                PATH_MAX_LEN - 1
            );
        } else {
            strncpy(
                out_rpath,
                rpath,
                PATH_MAX_LEN
            );
        }
    }
    return OK;
}
