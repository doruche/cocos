/*
 * processor management
 */

#pragma once

#include "libs/types.h"
#include "kernel/arch/ctx.h"
#include "kernel/task/sched.h"

typedef struct _processor_t {
    ctx_t   sched_ctx;  // context for scheduler/this processor
    task_t* cur_task; // maybe NULL when executing on scheduler context
} processor_t;

void    processor_init(void);
extern  processor_t processor;
#define current_task \
    (processor.cur_task)
#define scheduler_ctx \
    (&processor.sched_ctx)

void    wait_for_intr(void);
