/* 
 * Client <-> VFS protocol definitions
 */

#pragma once

#include <libs/prelude.h>
#include <config.h>

typedef enum {
    VFS_OPEN,
    VFS_OPEN_RESP,
    VFS_READ,
    VFS_READ_RESP,
    VFS_WRITE,
    VFS_WRITE_RESP,
    VFS_CLOSE,
    VFS_UNLINK,
    
    /*
     * in our microkernel design,
     * a filesystem is not a real kernel module,
     * but a process running in user space.
     * indeed we can implement something that
     * a filesystem server itself handles all its
     * mounting points internally, but it's less flexible.
     * the way we adopt: to mount a filesystem,
     * we spawn a new filesystem server process with
     * device and mount point as its arguments,
     * then fs itself will register to VFS with its mount point and fs type.
     * e.g. fat32 <device> /mnt/data
     */
    VFS_MOUNT,
} vfs_msg_type_t;

typedef struct {
    vfs_msg_type_t type;
    union {
        struct {
            char path[PATH_MAX_LEN];
            vfs_open_flags_t flags;            
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
            u8 data[256];
        } read_resp;
        struct {
            u64 fd;
            u64 size;
            u8 data[256];
        } write;
        struct {
            u64 size;
        } write_resp;
        struct {
            u64 fd;
        } close;
        struct {
            u64 fd;
        } unlink;

        struct {
            char path[PATH_MAX_LEN];
            /* vfs will communicate with fs server via tid */
        } mount;
    };
} vfs_msg_t;
