/*
 * Process Manager server protocol definitions
 */

#pragma once

#include <libs/prelude.h>

typedef enum _pm_msg_type_t {
    PM_PING,
    PM_PING_RESP,

#define SERVICE_NAME_MAX_LEN 32
    PM_RESOLVE_NAME,
    PM_PUBLISH,
    PM_UNPUBLISH,

    PM_MAP,
    PM_UNMAP,
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
    };
} pm_msg_t;

