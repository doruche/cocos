#include "name.h"
#include <libs/prelude.h>
#include <libs/list.h>
#include <libs/path.h>
#include <uspace/servers/pm.h>

static list_head(mounts);

result_t
s_ns_mount(const char* path, pid_t fs) {
    list_foreach(iter, &mounts) {
        struct mount* m = list_entry(iter, struct mount, node);
        if (strcmp(m->path, path) == 0 || m->fs == fs) {
            return -ERR_EXIST;
        }
    }
    struct mount* m = malloc(sizeof(*m));
    if (m == NULL) {
        return -ERR_NOMEM;
    }
    m->fs = fs;
    
    path_canonicalize((char*)path, m->path);
    list_push_back(&mounts, &m->node);
    return OK;
}

result_t
s_ns_umount(char* path) {
    path_canonicalize(path, path);
    list_foreach_safe(iter, &mounts, next) {
        struct mount* m = list_entry(iter, struct mount, node);
        if (strcmp(m->path, path) == 0) {
            list_remove(&m->node);
            
            bool to_unwatch = false;
            list_foreach(iter, &mounts) {
                struct mount* mm = list_entry(iter, struct mount, node);
                if (mm->fs == m->fs) {
                    to_unwatch = false;
                    break;
                }
                to_unwatch = true;
            }
            if (to_unwatch) {
                proc_unwatch(m->fs);
            }
        
            free(m);
            return OK;
        }
    }
    return -ERR_NOT_FOUND;
}

static usize
mountp_match(const char* path, const char* mountp) {
    usize len = strlen(mountp);
    if (strncmp(path, mountp, len) != 0) {
        return 0;
    }
    if (path[len] != '/' && path[len] != '\0') {
        return 0;
    }
    return len;
}

result_t
s_ns_resolve(
    char* path,
    pid_t* out_fs,
    char* out_rpath
) {
    struct mount* target = NULL;
    usize max_matched = 0;
    path_canonicalize(path, path);
    list_foreach(iter, &mounts) {
        struct mount* m = list_entry(iter, struct mount, node);
        usize matched = mountp_match(path, m->path);
        if (matched > max_matched) {
            max_matched = matched;
            target = m;
        }
    }
    if (target == NULL) {
        return -ERR_NOT_FOUND;
    }
    if (out_fs != NULL) {
        *out_fs = target->fs;
    }
    if (out_rpath != NULL) {
        const char* rpath = path + max_matched;
        /* add root slash */
        out_rpath[0] = '/';
        strncpy(out_rpath + 1, rpath, PATH_MAX_LEN - 1);
    }
    return OK;
}

void
s_ns_cleanup(pid_t fs) {
    list_foreach_safe(iter, &mounts, next) {
        struct mount* m = list_entry(iter, struct mount, node);
        if (m->fs == fs) {
            list_remove(&m->node);
            free(m);
            pr_info("ns: fs %ld exit. umount %s\n", fs, m->path);
        }
    }
}