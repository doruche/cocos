#include "kernel/syscall.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "libs/types.h"
#include "libs/macros.h"
#include "kernel/arch/ctx.h"
#include "libs/sysno.h"

static const syscall_ptr_t syscall_table[] = {
    [SYS_TASK_KILL]      __sys_task_kill,
    [SYS_TASK_GETTID]    __sys_task_gettid,
    [SYS_DBG_PUTS]      __sys_dbg_puts,
    [SYS_PM_ALLOC]      __sys_pm_alloc,
    [SYS_VM_MAP]      __sys_vm_map,
    [SYS_VM_UNMAP]      __sys_vm_unmap,
    [SYS_TASK_SPAWN]    __sys_task_spawn,
    [SYS_TASK_YIELD]    __sys_task_yield,
};

static const char* const syscall_strs[] = {
    [SYS_TASK_KILL]      = "task_kill",
    [SYS_TASK_GETTID]    = "task_gettid",
    [SYS_DBG_PUTS]      = "dbg_puts",
    [SYS_PM_ALLOC]      = "pm_alloc",
    [SYS_VM_MAP]      = "vm_map",
    [SYS_VM_UNMAP]      = "vm_unmap",
    [SYS_TASK_SPAWN]    = "task_spawn",
    [SYS_TASK_YIELD]    = "task_yield",
};

bool
do_syscall(
    u64 syscall_no,
    trapframe_t* tf
) {
    if (syscall_no >= array_size(syscall_table)) {
        return false;
    }
    if (syscall_table[syscall_no] == NULL) {
        return false;
    }
    // a0

    if (syscall_no != SYS_DBG_PUTS) {
        trace("do_syscall: syscall no=%ld (%s)",
            syscall_no,
            syscall_strs[syscall_no]
        );
    }

    u64 arg0 = tf->x[10];
    u64 arg1 = tf->x[11];
    u64 arg2 = tf->x[12];
    u64 arg3 = tf->x[13];
    u64 arg4 = tf->x[14];

    tf->x[10] = syscall_table[syscall_no](arg0, arg1, arg2, arg3, arg4);
    tf->sepc += 4;
    return true;
}