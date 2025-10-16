/*
 * scheduling related definitions
 */

#pragma once

#include "libs/types.h"
#include "kernel/mm/vm.h"
#include "kernel/arch/ctx.h"
#include "libs/list.h"

typedef u64 tid_t;

typedef enum _task_state_t {
    T_READY = 0,
    T_RUNNING,
    T_ZOMBIE,
} task_state_t;

typedef struct _task_t {
    arch_ctx_t ctx;

    tid_t tid;
    task_state_t state;
    vm_space_t* vms;
    list_elem_t node; // node in task list
} task_t;


task_t* task_spawn(void (*entry)(void));
void    task_exit(void);

void    sched(void);