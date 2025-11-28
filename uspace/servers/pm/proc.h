#pragma once

#include "ns.h"
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
    tid_t pid;
    asid_t asid;
    vpn_t brk;
    list_t watchers; /* list of proc_watcher_t */
    struct name_space* ns;
};

struct proc_watcher_t {
    tid_t watcher;
    list_elem_t node;
};

void
task_init(void);

result_t s_proc_get(tid_t pid, struct process_t** out_proc);
result_t s_proc_exit(tid_t pid, result_t exit_code);
result_t s_proc_watch(tid_t watcher, tid_t target);
result_t s_proc_unwatch(tid_t watcher, tid_t target);

result_t
s_proc_spawn(
    const char* path, /* actually no real effect. just record the name for debugging */
    const u8* elf,
    const cmdline_t* cmdline,
    struct name_space* ns,
    tid_t* out_pid
);
result_t s_proc_kill(tid_t pid);

result_t s_vm_map_anon(
    tid_t pid,
    usize npages,
    vpn_t* out
);
result_t s_vm_map_mmio(
    tid_t pid,
    ppn_t ppn,
    usize npages,
    vpn_t* out
);
result_t s_vm_unmap(
    tid_t pid,
    vpn_t vpn,
    usize npages
);
