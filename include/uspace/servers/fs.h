/*
 * VFS <-> FS protocol definitions
 * client  server
 */

#pragma once
#include <libs/prelude.h>

typedef enum {
    FS_GET,
    FS_GET_RESP,
    FS_READ,
    FS_READ_RESP,
    FS_WRITE,
    FS_WRITE_RESP,
    FS_PUT,

    FS_READDIR,
    FS_READDIR_RESP,
    FS_STAT,
    FS_STAT_RESP,
} fs_msg_type_t;

typedef struct {
    fs_msg_type_t type;
    union {
        struct {
            bool create;
            bool mkdir;
            char path[PATH_MAX_LEN];
        } get;
        struct {
            handle_t handle;
            vfs_st_mode_t mode;
        } get_resp;
        struct {
            handle_t handle;
            u64 offset;
            u64 size;
        } read;
        struct {
            u64 size;
            u8 data[256];
        } read_resp;
        struct {
            handle_t handle;
            u64 offset;
            u64 size;
            u8 data[256];
        } write;
        struct {
            u64 size;
        } write_resp;
        struct {
            bool unlink;
            bool rmdir;
            handle_t handle;
        } put;
        struct {
            handle_t handle;
            usize offset;
        } readdir;
        struct {
            vfs_dirent_t dirent;
            usize next_offset;
        } readdir_resp;
        struct {
            char path[PATH_MAX_LEN];
        } stat;
        struct {
            vfs_stat_t stat;
        } stat_resp;
    };
} fs_msg_t;

