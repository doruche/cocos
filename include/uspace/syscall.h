#pragma once

#include "libs/prelude.h"
#include "uspace/arch_syscall.h"

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
    port_t pager
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

static inline isize
sys_p_creat(port_t req_pid) {
    return arch_syscall(
        SYS_P_CREAT,
        (u64)(req_pid),
        0,
        0,
        0,
        0
    );
}

static inline isize
sys_p_close(port_t pid) {
    return arch_syscall(
        SYS_P_CLOSE,
        (u64)(pid),
        0,
        0,
        0,
        0
    );
}

static inline isize
sys_p_transfer(
    port_t pid,
    tid_t dst,
    port_flags_t flags
) {
    return arch_syscall(
        SYS_P_TRANSFER,
        (u64)(pid),
        (u64)(dst),
        (u64)(flags),
        0,
        0
    );
}

static inline isize
sys_p_send(const msg_hdr_t* msg) {
    return arch_syscall(
        SYS_P_SEND,
        (u64)(msg),
        0,
        0,
        0,
        0
    );
}

static inline isize
sys_p_recv(msg_hdr_t* msg) {
    return arch_syscall(
        SYS_P_RECV,
        (u64)(msg),
        0,
        0,
        0,
        0
    );
}

static inline isize
sys_task_block(tid_t tid) {
    return arch_syscall(
        SYS_TASK_BLOCK,
        (u64)(tid),
        0,
        0,
        0,
        0
    );
}

static inline isize
sys_task_resume(tid_t tid) {
    return arch_syscall(
        SYS_TASK_RESUME,
        (u64)(tid),
        0,
        0,
        0,
        0
    );
}

static inline isize
sys_p_stat(
    port_t pid,
    p_stat_t* stat
) {
    return arch_syscall(
        SYS_P_STAT,
        (u64)(pid),
        (u64)(stat),
        0,
        0,
        0
    );
}