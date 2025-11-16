/*
 * Echo server protocol definitions
 */

#pragma once

#include <libs/prelude.h>
#include <uspace/rpc.h>

typedef enum _echo_msg_id_t {
    ECHO_ECHO = 0,
} echo_msg_id_t;

#define ECHO_MSG_MAX_LEN 128

typedef struct _echo_msg_t {
    union {
        struct {
            struct {
                char data[ECHO_MSG_MAX_LEN];
                usize len;
                } echo;
            struct {
                char data[ECHO_MSG_MAX_LEN];
                usize len;
                } echo_resp;
        };
        u8 padding[RPC_MSG_SIZE];
    };
} echo_msg_t;

static_assert(sizeof(echo_msg_t) == RPC_MSG_SIZE);
