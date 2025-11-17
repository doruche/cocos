#pragma once

#include <libs/prelude.h>
#include <uspace/arch/syscall.h>

static inline result_t
sys_task_destroy(tid_t tid) {
    return arch_syscall(
        SYS_TASK_DESTROY,
        (u64)(tid),
        0,
        0,
        0,
        0
    );
}

static inline result_t
sys_task_gettid(void) {
    return arch_syscall(
        SYS_TASK_GETTID,
        0,
        0,
        0,
        0,
        0
    );
}

static inline result_t
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

static inline result_t
sys_task_spawn(
    const char* name,
    uaddr_t entry,
    asid_t asid
) {
    return arch_syscall(
        SYS_TASK_SPAWN,
        (u64)(name),
        (u64)(entry),
        (u64)(asid),
        0,
        0
    );
}

static inline result_t
sys_as_get(tid_t tid) {
    return arch_syscall(
        SYS_AS_GET,
        (u64)(tid),
        0,
        0,
        0,
        0
    );
}

static inline result_t
sys_as_map(
    asid_t asid,
    vpn_t vpn,
    ppn_t ppn,
    usize npages,
    vm_flags_t flags
) {
    return arch_syscall(
        SYS_AS_MAP,
        (u64)(asid),
        (u64)(vpn),
        (u64)(ppn),
        (u64)(npages),
        (u64)(flags)
    );
}

static inline result_t
sys_as_unmap(
    asid_t asid,
    vpn_t vpn,
    usize npages
) {
    return arch_syscall(
        SYS_AS_UNMAP,
        (u64)(asid),
        (u64)(vpn),
        (u64)(npages),
        0,
        0
    );
}

static inline result_t
sys_as_memcpy(
    asid_t asid,
    vaddr_t addr,
    const void* buf,
    usize len
) {
    return arch_syscall(
        SYS_AS_MEMCPY,
        (u64)(asid),
        (u64)(addr),
        (u64)(buf),
        (u64)(len),
        0
    );
}

static inline result_t
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

static inline result_t
sys_ipc(
    tid_t send_to,
    tid_t recv_from,
    msg_t* msg,
    ipc_flags_t flags
) {
    return arch_syscall(
        SYS_IPC,
        (u64)(send_to),
        (u64)(recv_from),
        (u64)(msg),
        (u64)(flags),
        0
    );
}

static inline result_t
sys_notify(tid_t tid, notif_t notifs) {
    return arch_syscall(
        SYS_NOTIFY,
        (u64)(tid),
        (u64)(notifs),
        0,
        0,
        0
    );
}

static inline result_t
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

static inline result_t
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

static inline void __noreturn
sys_task_exit(result_t exit_code) {
    arch_syscall(
        SYS_TASK_EXIT,
        (u64)(exit_code),
        0,
        0,
        0,
        0
    );
    unreachable();
}

static inline result_t
sys_task_getzombie(zombie_task_t* out) {
    return arch_syscall(
        SYS_TASK_GETZOMBIE,
        (u64)(out),
        0,
        0,
        0,
        0
    );
}

static inline result_t
sys_as_memset(
    asid_t asid,
    vaddr_t addr,
    u8 value,
    usize len
) {
    return arch_syscall(
        SYS_AS_MEMSET,
        (u64)(asid),
        (u64)(addr),
        (u64)(value),
        (u64)(len),
        0
    );
}

static inline result_t
sys_irq_listen(irq_t irqno) {
    return arch_syscall(
        SYS_IRQ_LISTEN,
        (u64)(irqno),
        0,
        0,
        0,
        0
    );
}

static inline result_t
sys_irq_unlisten(irq_t irqno) {
    return arch_syscall(
        SYS_IRQ_UNLISTEN,
        (u64)(irqno),
        0,
        0,
        0,
        0
    );
}
