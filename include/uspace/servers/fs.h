/* 
 * Client <-> VFS protocol definitions
 */

#pragma once

#include <libs/prelude.h>
#include <config.h>

typedef enum {
    FS_OPEN,
    FS_OPEN_RESP,
    FS_READ,
    FS_READ_RESP,
    FS_WRITE,
    FS_WRITE_RESP,
    FS_CLOSE,
    FS_UNLINK,

    FS_MKDIR,
    FS_READDIR,
    FS_READDIR_RESP,
    FS_RMDIR,
    
    FS_STAT,
    FS_STAT_RESP,
} fs_msg_type_t;

typedef struct {
    fs_msg_type_t type;
    union {
        struct {
            char path[PATH_MAX_LEN];
            u64 flags;
        } open;
        struct {
            u64 fd;
        } open_resp;
        struct {
            u64 fd;
            u64 size;
        } read;
        struct {
            u64 size;
            u8 data[1024];
        } read_resp;
        struct {
            u64 fd;
            u64 size;
            u8 data[1024];
        } write;
        struct {
            u64 size;
        } write_resp;
        struct {
            u64 fd;
        } close;
        struct {
            char path[PATH_MAX_LEN];
        } unlink;

        struct {
            char path[PATH_MAX_LEN];
        } mkdir;
        struct {
            u64 fd;
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
            stat_t stat;
        } stat_resp;
    };
} fs_msg_t;
