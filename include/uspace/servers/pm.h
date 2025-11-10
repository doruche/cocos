/*
 * Process Manager server protocol definitions
 */

#pragma once

#include <libs/prelude.h>

typedef enum _pm_msg_id_t {
    PM_PING = 0,
} pm_msg_id_t;

typedef union _pm_msgbody_t {
    struct {
        usize val;
    } ping;
    struct {
        usize val;
    } ping_resp;
} pm_msgbody_t;

typedef struct _pm_msg_t {
    union {
        struct {
            msg_hdr_t header;
            pm_msgbody_t body;
        };
        u8 padding[MSG_SIZE];
    };
} pm_msg_t;

static_assert(sizeof(pm_msg_t) == MSG_SIZE);
static_assert(offset_of(pm_msg_t, header) == 0);