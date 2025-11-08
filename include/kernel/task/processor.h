/*
 * processor management
 */

#pragma once

#include <libs/prelude.h>
#include <kernel/arch/arch.h>
#include <kernel/task/sched.h>

typedef struct _processor_t {
    arch_kctx_t sched_ctx;  // context for scheduler/this processor
    task_t* cur_task; // maybe NULL when executing on scheduler context
} processor_t;

void    processor_init(void);
extern  processor_t processor;
#define current_task \
    (processor.cur_task)
#define scheduler_ctx \
    (&processor.sched_ctx)

static inline bool
in_scheduler_ctx(void) {
    return current_task == NULL;
}
