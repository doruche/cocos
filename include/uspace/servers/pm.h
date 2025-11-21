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

    PM_SPAWN,
    PM_SPAWN_RESP,
    
    PM_WATCH,
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
            char cmdline[SERIAL_BUF_MAX_LEN];
        } spawn;
        struct {
            tid_t proc_tid;
        } spawn_resp;
        struct {
            tid_t watch_tid;
        } watch;
    };
} pm_msg_t;

