#pragma once
#include <libs/prelude.h>

#define NUM_ARGS_MAX 8
struct args_t {
    usize argc;
    char* argv[NUM_ARGS_MAX + 1]; /* +1 for null-termination */
};


struct cmd_t {
    const char* name;
    const char* desc;
    result_t (*handler)(const struct args_t* args);
};

result_t cmd_run(const struct args_t* args);
