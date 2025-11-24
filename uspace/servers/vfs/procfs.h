#pragma once
#include "file.h"
#include <libs/prelude.h>
#include <libs/list.h>
#include <config.h>

struct proc_file_t {
    struct fs_file_t* vfs_file;
    usize offset;
    vfs_open_flags_t flags;
};

struct process_t {
    pid_t pid;
    struct proc_file_t files[MAX_FDS_PER_PROC];
    list_elem_t node;
};

result_t proc_open(
    pid_t pid,
    const char* path,
    vfs_open_flags_t flags,
    u64* out_fd
);

void proc_exit(pid_t pid);

result_t proc_close(pid_t pid, u64 fd);

result_t proc_unlink(pid_t pid, u64 fd);

result_t proc_read(
    pid_t pid,
    u64 fd,
    u8* buf,
    u64 size,
    u64* out_size
);

result_t proc_write(
    pid_t pid,
    u64 fd,
    const u8* buf,
    u64 size,
    u64* out_size
);

