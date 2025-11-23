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
    pid_t* out_pid
);
result_t proc_watch(pid_t pid);
result_t proc_unwatch(pid_t pid);
result_t proc_join(pid_t pid, result_t* xcode);
