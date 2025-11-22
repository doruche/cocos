#pragma once

#include <libs/prelude.h>
#include <libs/list.h>
#include <config.h>

/*
 * the kernel does not actually have a sense of "process" or "thread",
 * it only has "task"s, a single schedulable entity. and in pm server,
 * we do distinguish "process" and "thread" by the way we associate
 * tasks and address spaces. 
 * So we say "task" inside kernel and pm's inner implementation,
 * but only expose "process" and "thread" concepts to other user space servers
 * and applications.
 */

/* currently, we only support single-threaded process */
struct process_t {
    bool in_use;
    
    char path[PATH_MAX_LEN];
    pid_t pid;
    asid_t asid;
    vpn_t brk;
};

void
task_init(void);

result_t proc_exit(pid_t pid, result_t exit_code);

result_t
pm_proc_spawn(
    const char* path, /* actually no real effect. just record the name for debugging */
    const u8* elf,
    const cmdline_t* cmdline,
    pid_t* out_pid
);
result_t
pm_proc_join(
    pid_t parent_pid,
    pid_t pid,
    result_t* exit_code
);

result_t
vm_map_anon(
    pid_t pid,
    usize npages,
    vpn_t* out
);
result_t
vm_map_mmio(
    pid_t pid,
    ppn_t ppn,
    usize npages,
    vpn_t* out
);
result_t vm_unmap(
    pid_t pid,
    vpn_t vpn,
    usize npages
);