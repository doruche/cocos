/*
 * Process Manager server protocol definitions
 */

#pragma once

#include <libs/prelude.h>
#include <libs/cmd.h>

typedef enum _pm_msg_type_t {
    PM_PING,
    PM_PING_RESP,

#define SERVICE_NAME_MAX_LEN 32
    PM_RESOLVE_NAME,
    PM_RESOLVE_NAME_RESP,
    PM_PUBLISH,
    PM_UNPUBLISH,

    PM_MAP,
    PM_MAP_RESP,
    PM_UNMAP,

    PM_PROC_SPAWN,
    PM_PROC_SPAWN_RESP,
    PM_PROC_PROBE,
    PM_PROC_WATCH,
    PM_PROC_UNWATCH,
    PM_PROC_EXIT,
    // PM_THREAD_XXX,
} pm_msg_type_t;

typedef struct _pm_msg_t {
    pm_msg_type_t type;
    union {
        struct {
            usize val;
        } ping;
        struct {
            usize val;
        } ping_resp;
        struct {
            char name[SERVICE_NAME_MAX_LEN];
        } resolve_name;
        struct {
            tid_t server_tid;
        } resolve_name_resp;
        struct {
            char name[SERVICE_NAME_MAX_LEN];
            tid_t server_tid;
        } publish;
        struct {
            char name[SERVICE_NAME_MAX_LEN];
        } unpublish;
        struct {
            enum {
                PM_MAP_ANON,
                PM_MAP_MMIO,
            } type;
            union {
                struct {
                    usize npages;
                } anon;
                struct {
                    ppn_t ppn;
                    usize npages;
                } mmio;
            } info;
        } map;
        struct {
            vpn_t vpn;
        } map_resp;
        struct {
            vpn_t vpn;
            usize npages;
        } unmap;
        struct {
            char path[PATH_MAX_LEN];
            char cmdline[SERIAL_BUF_MAX_LEN];
        } proc_spawn;
        struct {
            tid_t pid;
        } proc_spawn_resp;
        struct {
            pid_t pid;
        } proc_probe;
        struct {
            pid_t pid;
        } proc_watch;
        struct {
            pid_t pid;
        } proc_unwatch;
        struct {
            pid_t pid;
            result_t xcode;
        } proc_exit; /* response of proc_watch */
    };
} pm_msg_t;

