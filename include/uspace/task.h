#pragma once

#include <libs/prelude.h>

/* kernel primitives */
__noreturn
void    task_exit(result_t exit_code);
void    task_yield(void);
tid_t   task_gettid(void);

/* pm abstractions */
result_t proc_spawn(
    const char* path,
    const char* argv[],
    tid_t* out_pid
);
result_t proc_wait(
    tid_t pid,
    result_t* exit_code
);
