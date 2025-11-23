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
} fs_msg_type_t;

typedef struct {
    fs_msg_type_t type;
    union {
        struct {
            bool create;
            char path[PATH_MAX_LEN];
        } get;
        struct {
            handle_t handle;
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
            handle_t handle;
        } put;
    };
} fs_msg_t;

