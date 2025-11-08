/*
 * scheduling related definitions
 */

#pragma once

#include <libs/prelude.h>
#include <libs/list.h>
#include <kernel/mm/as.h>
#include <kernel/arch/arch.h>
#include <kernel/consts/params.h>

typedef enum _task_state_t {
    T_READY = 0,
    T_RUNNING,
    T_BLOCKED,
    T_ZOMBIE,
} task_state_t;

typedef struct _addr_space_t addr_space_t; // forward declaration
typedef struct _task_t {
    char name[TASK_NAME_MAX_LEN];
    arch_ctx_t* actx;
    tid_t tid __readonly;
    task_state_t state;
    addr_space_t* as;
    u8 msg_buf[MSG_MAX_SIZE]; // ipc buffer used for sending messages
    notifications_t notif; // pending notifications
    notifications_t notif_mask; // notification mask
    list_elem_t node_all; // node in all tasks list
    list_elem_t node_running; // node in running tasks list
    list_elem_t node_port_tx; // node in port's tx list
    list_elem_t node_port_wtx; // node in port's tx waitlist
    list_t port_list; // list of task_port_t owned by this task
} task_t;

// layout
// TRAMPOLINE
// task 0 kstack | guard page
// ...
kaddr_t task_kstack_top(tid_t tid);
result_t    task_get(tid_t tid, task_t** out);
void    task_yield(void);
result_t    task_block(tid_t tid);
result_t    task_resume(tid_t tid);

void    sched_init(u8* init_elf);

result_t task_spawn(
    const char* name, 
    uaddr_t entry, 
    asid_t asid,
    task_t** out
);
result_t    task_kill(tid_t tid);
void    task_crash_exit(void);

void    scheduler(void);