#include "proc.h"
#include "pns.h"
#include "ns.h"
#include <libs/prelude.h>
#include <libs/list.h>
#include <libs/path.h>

static list_head(name_spaces);

static nsid_t next_nsid = 1;
static nsid_t nsid_alloc(void) {
    if (next_nsid == NSID_INVALID) {
        panic("nsid_alloc: out of nsid");
    }
    return next_nsid++;
}

void
ns_init(void) {
    /* create global name space */
    struct name_space* ns = malloc(sizeof(*ns));
    assert(ns != NULL);
    ns->id = nsid_alloc();
    ns->rc = 1;
    list_init(&ns->mounts);
    list_push_back(&name_spaces, &ns->node);
}

struct name_space*
s_ns_global(void) {
    return list_entry(
        name_spaces.next,
        struct name_space,
        node
    );
}

/* DANGEROUS. caller should increase rc immediately (call bind) */
struct name_space*
s_ns_new(void) {
    struct name_space* ns = malloc(sizeof(*ns));
    assert(ns != NULL);
    ns->id = nsid_alloc();
    ns->rc = 0;
    list_init(&ns->mounts);
    list_push_back(&name_spaces, &ns->node);
    return ns;
}

void
s_ns_bind(struct name_space* ns, struct process_t* proc) {
    if (proc->ns != NULL) {
        s_ns_unbind(proc);
    }
    pr_info("s_ns_bind: binding process %ld to name space %ld",
        proc->pid, ns->id);
    proc->ns = ns;
    ns->rc++;
}

void
s_ns_unbind(struct process_t* proc) {
    struct name_space* ns = proc->ns;
    if (ns == NULL) {
        return;
    } 

    proc->ns = NULL;
    assert(ns->rc > 0);
    ns->rc--;
    if (ns->rc == 0) {
        pr_info("s_ns_unbind: freeing name space %ld", ns->id);
        list_foreach_safe(iter, &ns->mounts, next) {
            struct ns_mount* m = 
                list_entry(iter, struct ns_mount, node);
            list_remove(&m->node);
            free(m);
        }
        list_remove(&ns->node);
        free(ns);
    }
}

static usize
mountp_match(const char* path, const char* mountp) {
    usize len = strlen(mountp);
    if (len == 1 && mountp[0] == '/') {
        return 1; /* root mount point matches everything */
    }
    if (strncmp(path, mountp, len) != 0) {
        return 0;
    }
    if (path[len] != '/' && path[len] != '\0') {
        return 0;
    }
    return len;
}

result_t
s_ns_mount(
    struct name_space* ns,
    char* path,
    const char* owner
) {
    if (!path_is_absolute(path)) {
        return -ERR_INVAL;
    }
    if (is_err(pn_lookup(owner, &(tid_t){0}))) {
        return -ERR_NOT_FOUND;
    }
    path_canonicalize(path, path);
    list_foreach(iter, &ns->mounts) {
        struct ns_mount* m = list_entry(iter, struct ns_mount, node);
        if (strcmp(m->path, path) == 0) {
            return -ERR_EXIST;
        }
    }
    struct ns_mount* m = malloc(sizeof(*m));
    if (m == NULL) {
        return -ERR_NOMEM;
    }
    strncpy(m->owner, owner, SERVICE_NAME_MAX_LEN);
    strncpy(m->path, path, PATH_MAX_LEN);

    list_push_back(&ns->mounts, &m->node);
    return OK;
}

result_t
s_ns_umount(struct name_space* ns, char* path) {
    if (!path_is_absolute(path)) {
        return -ERR_INVAL;
    }
    path_canonicalize(path, path);
    list_foreach_safe(iter, &ns->mounts, next) {
        struct ns_mount* m = list_entry(iter, struct ns_mount, node);
        if (strcmp(m->path, path) == 0) {
            list_remove(&m->node);
            free(m);
            return OK;
        }
    }
    return -ERR_NOT_FOUND;
}

result_t
s_ns_resolve(
    struct name_space* ns,
    char* path,
    tid_t* out_owner,
    char* out_rpath
) {
    if (!path_is_absolute(path)) {
        return -ERR_INVAL;
    }
    path_canonicalize(path, path);
    usize max_matched = 0;
    struct ns_mount* target = NULL;
    list_foreach(iter, &ns->mounts) {
        struct ns_mount* m = list_entry(iter, struct ns_mount, node);
        usize matched = mountp_match(path, m->path);
        if (matched > max_matched) {
            max_matched = matched;
            target = m;
        }
    }
    if (max_matched == 0) {
        pr_info("s_ns_resolve: no mount point matched for path %s", path);
        return -ERR_NOT_FOUND;
    }
    tid_t tmp;
    if (is_err(pn_lookup(target->owner, &tmp))) {
        return -ERR_NOT_FOUND;
    }
    if (out_owner != NULL) {
        *out_owner = tmp;
    }
    if (out_rpath != NULL) {
        const char* rpath = path + max_matched;
        /* add root slash */
        out_rpath[0] = '/';
        strncpy(out_rpath + 1, rpath, PATH_MAX_LEN - 1);
    }

    return OK;
}
