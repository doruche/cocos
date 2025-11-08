#pragma once

#include <libs/prelude.h>

__noreturn
void    task_exit(result_t exit_code);
void    task_yield(void);
tid_t   task_gettid(void);