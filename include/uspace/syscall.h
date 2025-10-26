#pragma once

#include "libs/prelude.h"
#include "uspace/arch_syscall.h"
#include "libs/sysno.h"

static inline isize
sys_task_kill(tid_t tid) {
    return (isize)arch_syscall(
        SYS_TASK_KILL,
        (u64)(tid),
        0,
        0,
        0,
        0
    );
}

static inline isize
sys_task_gettid(void) {
    return (isize)arch_syscall(
        SYS_TASK_GETTID,
        0,
        0,
        0,
        0,
        0
    );
}

static inline isize
sys_dbg_puts(const char* str, usize len) {
    return arch_syscall(
        SYS_DBG_PUTS,
        (u64)(str),
        (u64)(len),
        0,
        0,
        0
    );
}

static inline isize
sys_task_spawn(
    const char* name,
    uaddr_t entry,
    tid_t pager
) {
    return arch_syscall(
        SYS_TASK_SPAWN,
        (u64)(name),
        (u64)(entry),
        (u64)(pager),
        0,
        0
    );
}

static inline isize
sys_pm_alloc(
    tid_t tid
) {
    return arch_syscall(
        SYS_PM_ALLOC,
        (u64)(tid),
        0,
        0,
        0,
        0
    );
}

static inline isize
sys_vm_map(
    tid_t tid,
    vpn_t vpn,
    ppn_t ppn,
    usize npages,
    vm_flags_t flags
) {
    return arch_syscall(
        SYS_VM_MAP,
        (u64)(tid),
        (u64)(vpn),
        (u64)(ppn),
        (u64)(npages),
        (u64)(flags)
    );
}

static inline isize
sys_vm_unmap(
    tid_t tid,
    vpn_t vpn,
    usize npages
) {
    return arch_syscall(
        SYS_VM_UNMAP,
        (u64)(tid),
        (u64)(vpn),
        (u64)(npages),
        0,
        0
    );
}

static inline isize
sys_task_yield(void) {
    return arch_syscall(
        SYS_TASK_YIELD,
        0,
        0,
        0,
        0,
        0
    );
}
