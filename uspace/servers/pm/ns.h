#pragma once
#include <libs/prelude.h>
#include <libs/list.h>


/*
 * a name space is a mapping from path strings to objects,
 * such as files, devices, or services.
 * different processes can have different name spaces,
 * or share the same name space, thus achieving isolation or sharing as needed.
 * a name space can be considered as a view of the global system resources,
 * and processes can add or remove mappings in their own name spaces.
 * 
 * name spaces are just dumb. they don't care whether it's a valid file system,
 * or whether the target process actually exists. they just maintain the mappings.
 * if you mount a wrong file system, they it's user's fault. and that's why
 * we allow each process to have its own name space - isolation.
 * 
 * note that name spaces does not specify the way processes access the objects,
 * it only provides a way to resolve names to target tids. e.g.,
 * a file path can be resolved to the tid of the filesystem server,
 * and the process can then communicate with the filesystem server
 * to perform file operations. or a device name can be resolved to the tid of the device driver,
 * and the process can then send requests to the device driver to interact with the device.
 * in this way, name spaces are just some kind of mapping tables,
 * and the actual access mechanisms are handled by other components.
 * 
 */

struct ns_mount {
    char path[PATH_MAX_LEN];
    char owner[SERVICE_NAME_MAX_LEN];
    list_elem_t node;
};

struct name_space {
    nsid_t id;
    usize rc;
    list_t mounts;
    list_elem_t node;
};

struct process_t;

void ns_init(void);
struct name_space* s_ns_global(void);
struct name_space* s_ns_new();
void s_ns_bind(struct name_space* ns, struct process_t* proc);
void s_ns_unbind(struct process_t* proc);
result_t s_ns_mount(
    struct name_space* ns,
    char *path,
    const char* owner
);
result_t s_ns_umount(
    struct name_space* ns,
    char *path
);
result_t s_ns_resolve(
    struct name_space* ns,
    char* path,
    tid_t* out_owner,
    char* out_rpath
);
