/*
 * example server message protocol definitions
 */

#pragma once

#include <libs/prelude.h>
#include <uspace/rpc.h>

typedef enum _example_msg_id_t {
    EXAMPLE_FOO = 0,
} example_msg_id_t;

typedef struct _example_msg_t {
    union {
        struct {
            example_msg_id_t id;
            union {
                struct {
                    u32 a;
                    u32 b;
                } foo_req;
                struct {
                    u32 result;
                } foo_resp;
            };
        };
        u8 padding[RPC_MSG_SIZE];
    };
} example_msg_t;

static_assert(sizeof(example_msg_t) == RPC_MSG_SIZE);
