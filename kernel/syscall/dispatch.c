#include <libs/prelude.h>
#include <kernel/arch/arch.h>
#include <kernel/syscall.h>

static const syscall_ptr_t syscall_table[] = {
    [SYS_TASK_KILL]      __sys_task_kill,
    [SYS_TASK_GETTID]    __sys_task_gettid,
    [SYS_DBG_PUTS]      __sys_dbg_puts,
    [SYS_AS_GET]       __sys_as_get,
    [SYS_AS_MAP]      __sys_as_map,
    [SYS_AS_UNMAP]    __sys_as_unmap,
    [SYS_AS_WRITE]    __sys_as_write,
    [SYS_TASK_SPAWN]    __sys_task_spawn,
    [SYS_TASK_YIELD]    __sys_task_yield,
    [SYS_P_CREAT]      __sys_p_creat,
    [SYS_P_CLOSE]      __sys_p_close,
    [SYS_P_TRANSFER]   __sys_p_transfer,
    [SYS_P_SEND]      __sys_p_send,
    [SYS_P_RECV]      __sys_p_recv,
    [SYS_TASK_BLOCK]  __sys_task_block,
    [SYS_TASK_RESUME] __sys_task_resume,
    [SYS_P_STAT]      __sys_p_stat,
    [SYS_P_NOTIFY]    __sys_p_notify,
    [SYS_TASK_EXIT]    __sys_task_exit,
};

static const char* const syscall_strs[] = {
    [SYS_TASK_KILL]      = "task_kill",
    [SYS_TASK_GETTID]    = "task_gettid",
    [SYS_DBG_PUTS]      = "dbg_puts",
    [SYS_AS_GET]       = "as_get",
    [SYS_AS_MAP]      = "as_map",
    [SYS_AS_UNMAP]    = "as_unmap",
    [SYS_AS_WRITE]    = "as_write",
    [SYS_TASK_SPAWN]    = "task_spawn",
    [SYS_TASK_YIELD]    = "task_yield",
    [SYS_P_CREAT]      = "p_creat",
    [SYS_P_CLOSE]      = "p_close",
    [SYS_P_TRANSFER]   = "p_transfer",
    [SYS_P_SEND]      = "p_send",
    [SYS_P_RECV]      = "p_recv",
    [SYS_TASK_BLOCK]  = "task_block",
    [SYS_TASK_RESUME] = "task_resume",
    [SYS_P_STAT]      = "p_stat",
    [SYS_P_NOTIFY]    = "p_notify",
    [SYS_TASK_EXIT]    = "task_exit",
};

result_t
syscall_dispatch(
    u64 syscall_no,
    arch_trapframe_t* tf
) {
    if (syscall_no >= array_size(syscall_table)) {
        warn("syscall_dispatch: invalid syscall no=%ld", syscall_no);
        return -ERR_NOENT;
    }
    if (syscall_table[syscall_no] == NULL) {
        warn("syscall_dispatch: unimplemented syscall no=%ld", syscall_no);
        return -ERR_NOENT;
    }

    if (syscall_no != SYS_DBG_PUTS) {
        trace("do_syscall: syscall no=%ld (%s)",
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