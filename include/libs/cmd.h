/*
 * command line related functions and definitions
 */

#pragma once
#include <libs/prelude.h>
#include <config.h>

typedef struct _cmdline_t {
    usize argc;
    char* argv[NUM_CMD_ARGS_MAX + 1]; /* +1 for null-termination */
} cmdline_t;

void cmd_skip_empty(char** cmd_str);
void cmd_parse_inplace(char* input, cmdline_t* out);
