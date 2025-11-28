/*
 * file descriptor 
 * since we do not support inter-process shared fd table,
 * fd_t is just a user-space representation of an open file.
 * and we can directly implement those fd-related operations
 * in libc.
 */
#pragma once
#include <libs/prelude.h>

typedef struct {
    bool in_use;

    handle_t fs_handle; /* for communicate with fs server */
    u64 id;
    tid_t fs;
    usize offset;
    u64 flags;
} fd_t;

const char* pwd(void);
result_t chdir(const char* path);

result_t open(const char* path, u64 flags, u64* out);
result_t close(u64 fd);
result_t read(u64 fd, void* buffer, u64 size, usize* bytes_read);
result_t write(u64 fd, const void* buffer, u64 size, usize* bytes_written);
result_t lseek(u64 fd, isize offset, seek_whence_t whence);
result_t stat(const char* path, stat_t* out);
result_t fstat(u64 fd, stat_t* out);
