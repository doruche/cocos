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
    };
} pm_msg_t;

