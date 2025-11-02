/*
 * Process Manager server protocol definitions
 */

#pragma once

#include "libs/prelude.h"

typedef enum _pm_msg_id_t {
    PM_REQ_PING = 0,
} pm_msg_id_t;

typedef union _pm_msgbody_t {
    struct {
        usize val;
    } ping;
} pm_msgbody_t;

typedef struct _pm_msg_t {
    msg_hdr_t header;
    pm_msgbody_t body;
} pm_msg_t;

static_assert(sizeof(pm_msg_t) <= MSG_MAX_SIZE);
static_assert(offset_of(pm_msg_t, header) == 0);