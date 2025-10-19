#include "kernel/syscall.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "libs/types.h"
#include "libs/macros.h"
#include "kernel/arch/ctx.h"
#include "libs/sysno.h"

static const syscall_ptr_t syscall_table[] = {
    [SYS_KILL]      __sys_kill,
    [SYS_GETTID]    __sys_gettid,
    [SYS_PUTS]      __sys_puts,
};

static const char* const syscall_strs[] = {
    [SYS_KILL]      = "kill",
    [SYS_GETTID]    = "gettid",
    [SYS_PUTS]      = "puts",
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

    trace("do_syscall: syscall no=%ld (%s)",
        syscall_no,
        syscall_strs[syscall_no]
    );

    u64 arg0 = tf->x[10];
    u64 arg1 = tf->x[11];
    u64 arg2 = tf->x[12];

    tf->x[10] = syscall_table[syscall_no](arg0, arg1, arg2);
    tf->sepc += 4;
    return true;
}