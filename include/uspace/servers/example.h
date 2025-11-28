/*
 * example server message protocol definitions
 */

#pragma once

#include <libs/prelude.h>

typedef enum {
    EXAMPLE_FOO,
    EXAMPLE_FOO_RESP,
} example_msg_type_t;

typedef struct {
    example_msg_type_t type;
    union {
        struct {
            u32 a;
            u32 b;
        } foo;
        struct {
            u32 result;
        } foo_resp;
    };
} example_msg_t;

/* 
 * rpc call encapsulations... 
 * e.g. result_t example_foo(u32 a, u32 b, u32* out_result);
 */
