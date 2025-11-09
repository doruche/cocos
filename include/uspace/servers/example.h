/*
 * example server message protocol definitions
 */

#pragma once

#include <libs/prelude.h>

typedef enum _example_msg_id_t {
    EXAMPLE_REQ_FOO = 0,
} example_msg_id_t;

typedef union _example_msgbody_t {
    struct {
        usize foo_val;
    } foo;
} example_msgbody_t;

typedef struct _example_msg_t {
    union {
        struct {
            msg_hdr_t header;
            example_msgbody_t body;
        };
        u8 padding[MSG_MAX_SIZE];
    };
} example_msg_t;

static_assert(sizeof(example_msg_t) == MSG_MAX_SIZE);
static_assert(offset_of(example_msg_t, header) == 0);