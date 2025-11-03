/*
 * Echo server protocol definitions
 */

#pragma once

#include "libs/prelude.h"

typedef enum _echo_msg_id_t {
    ECHO_REQ_ECHO = 0,
} echo_msg_id_t;

#define ECHO_MSG_MAX_LEN 128

typedef union _echo_msgbody_t {
    struct {
        char data[ECHO_MSG_MAX_LEN];
        usize len;
    } echo;
} echo_msgbody_t;

typedef struct _echo_msg_t {
    union {
        struct {
            msg_hdr_t header;
            echo_msgbody_t body;
        };
        u8 padding[MSG_MAX_SIZE];
    };
} echo_msg_t;

static_assert(sizeof(echo_msg_t) == MSG_MAX_SIZE);
static_assert(offset_of(echo_msg_t, header) == 0);