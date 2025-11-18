#include <libs/prelude.h>
#include <kernel/arch/arch.h>
#include <kernel/syscall.h>

static const syscall_ptr_t syscall_table[] = {
    [SYS_TASK_DESTROY]      __sys_task_destroy,
    [SYS_TASK_GETTID]    __sys_task_gettid,
    [SYS_DBG_PUTS]      __sys_dbg_puts,
    [SYS_AS_GET]       __sys_as_get,
    [SYS_AS_MAP]      __sys_as_map,
    [SYS_AS_UNMAP]    __sys_as_unmap,
    [SYS_AS_MEMCPY]   __sys_as_memcpy,
    [SYS_TASK_SPAWN]    __sys_task_spawn,
    [SYS_TASK_YIELD]    __sys_task_yield,
    [SYS_IPC]      __sys_ipc,
    [SYS_NOTIFY]   __sys_notify,
    [SYS_TASK_BLOCK]  __sys_task_block,
    [SYS_TASK_RESUME] __sys_task_resume,
    [SYS_TASK_EXIT]    __sys_task_exit,
    [SYS_TASK_GETZOMBIE]  __sys_task_getzombie,
    [SYS_AS_MEMSET]   __sys_as_memset,
    [SYS_IRQ_LISTEN]   __sys_irq_listen,
    [SYS_IRQ_UNLISTEN] __sys_irq_unlisten,
    [SYS_IRQ_ACK]     __sys_irq_ack,
};

static const char* const syscall_strs[] = {
    [SYS_TASK_DESTROY]      = "task_destroy",
    [SYS_TASK_GETTID]    = "task_gettid",
    [SYS_DBG_PUTS]      = "dbg_puts",
    [SYS_AS_GET]       = "as_get",
    [SYS_AS_MAP]      = "as_map",
    [SYS_AS_UNMAP]    = "as_unmap",
    [SYS_AS_MEMCPY]   = "as_memcpy",
    [SYS_TASK_SPAWN]    = "task_spawn",
    [SYS_TASK_YIELD]    = "task_yield",
    [SYS_IPC]      = "ipc",
    [SYS_NOTIFY]   = "notify",
    [SYS_TASK_BLOCK]  = "task_block",
    [SYS_TASK_RESUME] = "task_resume",
    [SYS_TASK_EXIT]    = "task_exit",
    [SYS_TASK_GETZOMBIE]  = "task_getzombie",
    [SYS_AS_MEMSET]   = "as_memset",
    [SYS_IRQ_LISTEN]   = "irq_listen",
    [SYS_IRQ_UNLISTEN] = "irq_unlisten",
    [SYS_IRQ_ACK]     = "irq_ack",
};

result_t
syscall_dispatch(
    u64 syscall_no,
    arch_trapframe_t* tf
) {
    if (syscall_no >= array_size(syscall_table)) {
        pr_warn("syscall_dispatch: invalid syscall no=%ld", syscall_no);
        return -ERR_NOENT;
    }
    if (syscall_table[syscall_no] == NULL) {
        pr_warn("syscall_dispatch: unimplemented syscall no=%ld", syscall_no);
        return -ERR_NOENT;
    }

    if (syscall_no != SYS_DBG_PUTS) {
        pr_trace("do_syscall: syscall no=%ld (%s)",
            syscall_no,
            syscall_strs[syscall_no]
        );
    }

    arch_store_syscall_ret(
        tf,
        syscall_table[syscall_no](
            arch_syscall_arg(tf, 0),
            arch_syscall_arg(tf, 1),
            arch_syscall_arg(tf, 2),
            arch_syscall_arg(tf, 3),
            arch_syscall_arg(tf, 4)
        )
    );

    return OK;
}