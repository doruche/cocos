#pragma once
#include <libs/prelude.h>
#include <libs/list.h>
#include <uspace/servers/vfs.h>

struct filesystem_t {
    pid_t fs;
    char mountp[PATH_MAX_LEN];
    list_elem_t node;    
};

result_t vfs_mount(
    pid_t fs,
    const char* mountp
);

void vfs_umount(pid_t fs);

result_t vfs_resolve(
    const char* path,
    struct filesystem_t** out_fss,
    char* out_rpath
);
