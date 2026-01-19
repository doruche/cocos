/*
 * scheduling related definitions
 */

#pragma once

#include <config.h>
#include <kernel/arch/arch.h>
#include <kernel/mm/as.h>
#include <libs/list.h>
#include <libs/prelude.h>

typedef enum _task_state_t {
  T_READY = 0,
  T_RUNNING,
  T_BLOCKED,
  T_ZOMBIE,
} task_state_t;

typedef struct _addr_space_t addr_space_t; /* forward declaration */
typedef struct _task_t {
  char name[PATH_MAX_LEN];
  tid_t tid __readonly;
  task_state_t state;
  arch_ctx_t *actx;
  addr_space_t *as;

  /* ipc */
  msg_t msg;      /* ipc buffer used for sending messages */
  notif_t notifs; /* notifications bitmap */
  /*
   * which task this task is willing to receive messages from
   * can be a specific tid, IPC_OPEN or TID_INVALID (except TID_KERNEL,
   * which is used only in message headers to indicate kernel source).
   */
  tid_t listen_on;
  list_t sender_list;        /* tasks blocking on sending to this task */
  list_elem_t node_sender;   /* node in sender list of another task */
  list_t receiver_list;      /* tasks blocking on receiving from this task */
  list_elem_t node_receiver; /* node in receiver list of another task */

  /* scheduling */
  result_t exit_code;       /* user space exit code */
  list_elem_t node_all;     /* node in all tasks list */
  list_elem_t node_running; /* node in running tasks list */
  list_elem_t node_zombie;  /* node in zombie tasks list */
} task_t;

// layout
// TRAMPOLINE
// task 0 kstack | guard page
// ...
kaddr_t task_kstack_top(tid_t tid);
result_t task_get(tid_t tid, task_t **out);
void task_yield(void);
void task_switch_to(tid_t tid);
result_t task_kill(tid_t tid);
result_t task_block(tid_t tid);
result_t task_resume(tid_t tid);

void sched_init(u8 *init_elf);

result_t task_spawn(const char *name, uaddr_t entry, uaddr_t sp, asid_t asid,
                    task_t **out);
void __noreturn task_exit(result_t exit_code);
result_t task_destroy(tid_t tid);
result_t task_getzombie(zombie_task_t *out);

void scheduler(void);