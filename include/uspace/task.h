#pragma once

#include "libs/types.h"

__noreturn
void    task_exit(void);
void    task_yield(void);
tid_t   task_gettid(void);