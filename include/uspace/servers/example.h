/*
 * example server message protocol definitions
 */

#pragma once

#include <libs/prelude.h>

typedef enum _example_msg_type_t {
    EXAMPLE_FOO,
    EXAMPLE_FOO_RESP,
} example_msg_type_t;

typedef struct _example_msg_t {
    example_msg_type_t type;
    union {
        struct {
            u32 a;
            u32 b;
        } foo_req;
        struct {
            u32 result;
        } foo_resp;
    };
} example_msg_t;

