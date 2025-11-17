/*
 * Echo server protocol definitions
 */
#pragma once

#include <libs/prelude.h>

#define ECHO_MSG_MAX_LEN 128

typedef enum _echo_msg_type_t {
    ECHO_ECHO,
    ECHO_ECHO_RESP,
} echo_msg_type_t;

typedef struct _echo_msg_t {
    echo_msg_type_t type;
    union {
        struct {
            char data[ECHO_MSG_MAX_LEN];
            usize len;
            } echo;
        struct {
            char data[ECHO_MSG_MAX_LEN];
            usize len;
            } echo_resp;
    };
} echo_msg_t;

