/*
 * Process Manager server protocol definitions
 */

#pragma once

#include <libs/prelude.h>
#include <uspace/rpc.h>

typedef enum _pm_msg_id_t {
    PM_PING = 0,
} pm_msg_id_t;

typedef struct _pm_msg_t {
    union {
        struct {
            struct {
                usize val;
            } ping;
            struct {
                usize val;
            } ping_resp;
        };
        u8 padding[RPC_MSG_SIZE];
    };
} pm_msg_t;

static_assert(sizeof(pm_msg_t) == RPC_MSG_SIZE);