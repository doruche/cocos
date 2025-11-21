#pragma once

#include <libs/prelude.h>
#include <config.h>

/*
 * although the kernel supports infinite tasks on theory,
 * we limit the max number of tasks in user space for simplicity.
 * (why? can it really simplify anything? probably not much...
 * idk. just leave it as is for now.)
 */
#define MAX_TASK_NUM 64

/*
 * the kernel does not actually have a sense of "process" or "thread",
 * it only has "task", a single schedulable entity. and in pm server,
 * we do distinguish "process" and "thread" by the way we associate
 * tasks and address spaces. 
 * So we say "task" inside kernel and pm's inner implementation,
 * but only expose "process" and "thread" concepts to other user space servers
 * and applications.
 */
struct task_t {
    bool in_use;
    tid_t tid;
    char name[TASK_NAME_MAX_LEN];
    asid_t asid;
    vpn_t brk;
};

void
task_init(void);

result_t task_alloc(struct task_t** out_task);
result_t task_get(tid_t tid, struct task_t** out_task);
result_t task_free(tid_t tid);

result_t
proc_spawn(
    const char* name,
    const u8* elf,
    const cmdline_t* cmdline,
    tid_t* out_tid
);

result_t
vm_map_anon(
    tid_t tid,
    usize npages,
    vpn_t* out
);
result_t
vm_map_mmio(
    tid_t tid,
    ppn_t ppn,
    usize npages,
    vpn_t* out
);
result_t vm_unmap(
    tid_t tid,
    vpn_t vpn,
    usize npages
);