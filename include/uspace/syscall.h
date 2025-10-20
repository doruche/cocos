#pragma once

#include "libs/types.h"
#include "uspace/arch_syscall.h"
#include "libs/sysno.h"

static inline isize
sys_kill(tid_t tid) {
    return (isize)arch_syscall(
        SYS_KILL,
        (u64)(tid),
        0,
        0
    );
}

static inline isize
sys_gettid(void) {
    return (isize)arch_syscall(
        SYS_GETTID,
        0,
        0,
        0
    );
}

static inline void
sys_puts(const char* str) {
    arch_syscall(
        SYS_PUTS,
        (u64)(str),
        0,
        0
    );
}