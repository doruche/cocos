#pragma once
#include <libs/prelude.h>
#include <libs/list.h>

struct mount {
    char path[PATH_MAX_LEN];
    pid_t fs;
    list_elem_t node;
};

result_t s_ns_mount(const char *path, pid_t fs);
result_t s_ns_umount(char *path);
result_t s_ns_resolve(
    char* path,
    pid_t* out_fs,
    char* out_rpath
);

void s_ns_cleanup(pid_t fs);