#pragma once

#include <libs/prelude.h>
#include <libs/handle.h>
#include <config.h>

/*
 * for simplicity we do not support ool data in fs messages
 * so we limit max io size to 1024 bytes 
 */
#define FS_MAX_IO_SIZE 1024

typedef enum {
    FS_GET,
    FS_GET_RESP,
    FS_READ,
    FS_READ_RESP,
    FS_WRITE,
    FS_WRITE_RESP,
    FS_UNLINK,

    FS_MKDIR,
    FS_READDIR,
    FS_READDIR_RESP,
    FS_RMDIR,
    
    FS_STAT,
    FS_FSTAT,
    FS_STAT_RESP,

    /* FS_IOCTL */
} fs_msg_type_t;

typedef struct {
    fs_msg_type_t type;
    union {
        struct {
            char path[PATH_MAX_LEN];
        } get;
        struct {
            handle_t handle;
        } get_resp;
        struct {
            handle_t handle;
            u64 size;
            usize offset;
        } read;
        struct {
            u64 size;
            u8 data[1024];
        } read_resp;
        struct {
            handle_t handle;
            u64 size;
            usize offset;
            u8 data[1024];
        } write;
        struct {
            u64 size;
        } write_resp;
        struct {
            char path[PATH_MAX_LEN];
        } unlink;

        struct {
            char path[PATH_MAX_LEN];
        } mkdir;
        struct {
            handle_t handle;
            usize offset;
        } readdir;
        struct {
            dirent_t dirent;
            usize next_offset;
        } readdir_resp;
        struct {
            char path[PATH_MAX_LEN];
        } rmdir;

        struct {
            char path[PATH_MAX_LEN];
        } stat;
        struct {
            handle_t handle;
        } fstat;
        struct {
            stat_t stat;
        } stat_resp;
    };
} fs_msg_t;

result_t fs_get(
    tid_t fs,
    const char* path, 
    handle_t* out
);
result_t fs_read(
    tid_t fs,
    handle_t handle,
    u8* buffer,
    u64 size,
    usize offset,
    usize* bytes_read
);
result_t fs_write(
    tid_t fs,
    handle_t handle,
    const u8* buffer,
    u64 size,
    usize offset,
    usize* bytes_written
);
result_t fs_unlink(tid_t fs, const char* path);
result_t fs_mkdir(tid_t fs, const char* path);
result_t fs_readdir(
    tid_t fs,
    handle_t handle,
    usize offset,
    dirent_t* out,
    usize* next_offset
);
result_t fs_rmdir(tid_t fs, const char* path);
result_t fs_stat(tid_t fs, const char* path, stat_t* out);
result_t fs_fstat(tid_t fs, handle_t handle, stat_t* out);
