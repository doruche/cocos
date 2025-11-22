#pragma once
#include <libs/prelude.h>
#include <libs/cmd.h>

struct builtin_cmd {
    const char* name;
    const char* desc;
    result_t (*handler)(const cmdline_t* cmdline);
};

result_t builtin_run(const cmdline_t* cmdline, bool* exist);
