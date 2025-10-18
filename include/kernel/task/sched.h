/*
 * scheduling related definitions
 */

#pragma once

#include "libs/types.h"
#include "kernel/mm/vm.h"
#include "kernel/arch/ctx.h"
#include "libs/list.h"
#include "kernel/consts/params.h"

typedef u64 tid_t;

typedef enum _task_state_t {
    T_READY = 0,
    T_RUNNING,
    T_ZOMBIE,
} task_state_t;

typedef struct _task_t {
    char name[TASK_NAME_MAX_LEN];

    arch_ctx_t actx;

    tid_t tid;
    tid_t pager;
    task_state_t state;
    vm_space_t* vms; // keep this as a pointer for easy shared memory management later
    list_elem_t node; // node in task list
} task_t;

// layout
// TRAMPOLINE
// scheduler kstack | guard page
// task 0 kstack | guard page
// ...
kaddr_t task_kstack_top(tid_t tid);
task_t* task_get(tid_t tid);

typedef struct _bootinfo_t bootinfo_t;
void    sched_init(u8* init_elf);

task_t* task_spawn(const char* name, uaddr_t entry);
void    task_kill(tid_t tid);
void    task_crash_exit(void);

void    yield(void);
void    scheduler(void);