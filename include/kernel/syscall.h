/*
 * syscall handler interface.
 */

#pragma once

#include "kernel/arch/ctx.h"
#include "kernel/task/sched.h"
#include "libs/types.h"
#include "kernel/task/processor.h"
#include "libs/sysno.h"

typedef u64 (*syscall_ptr_t)(
    u64, u64, u64
);

bool    do_syscall(
    u64 syscall_no, 
    trapframe_t* tf
);

/* helpers */

static inline u64
syscall_arg0() {
    return current_task->actx.tf.x[10];
}

static inline u64
syscall_arg1() {
    return current_task->actx.tf.x[11];
}

static inline u64
syscall_arg2() {
    return current_task->actx.tf.x[12];
}

#define SYSCALL_DEFINE0(name) \
    u64 __sys_##name( \
        u64 __arg0, u64 __arg1, u64 __arg2 \
    ) { \
        return sys_##name(); \
    } \
    isize sys_##name(void)
#define SYSCALL_DECLARE0(name) \
    u64 __sys_##name(u64, u64, u64); \
    isize sys_##name(void);

#define SYSCALL_DEFINE1(name, type0, arg0) \
    u64 __sys_##name( \
        u64 __arg0, u64 __arg1, u64 __arg2 \
    ) { \
        type0 arg0 = (type0)__arg0; \
        return (u64)sys_##name(arg0); \
    } \
    isize sys_##name(type0 arg0)
#define SYSCALL_DECLARE1(name, type0, arg0) \
    u64 __sys_##name(u64, u64, u64); \
    isize sys_##name(type0 arg0);

#define SYSCALL_DEFINE2(name, type0, arg0, type1, arg1) \
    u64 __sys_##name( \
        u64 __arg0, u64 __arg1, u64 __arg2 \
    ) { \
        type0 arg0 = (type0)__arg0; \
        type1 arg1 = (type1)__arg1; \
        return sys_##name(arg0, arg1); \
    } \
    isize sys_##name(type0 arg0, type1 arg1)
#define SYSCALL_DECLARE2(name, type0, arg0, type1, arg1) \
    u64 __sys_##name(u64, u64, u64); \
    isize sys_##name(type0 arg0, type1 arg1);

#define SYSCALL_DEFINE3(name, type0, arg0, type1, arg1, type2, arg2) \
    u64 __sys_##name( \
        u64 __arg0, u64 __arg1, u64 __arg2 \
    ) { \
        type0 arg0 = (type0)__arg0; \
        type1 arg1 = (type1)__arg1; \
        type2 arg2 = (type2)__arg2; \
        return sys_##name(arg0, arg1, arg2); \
    } \
    isize sys_##name(type0 arg0, type1 arg1, type2 arg2)
#define SYSCALL_DECLARE3(name, type0, arg0, type1, arg1, type2, arg2) \
    u64 __sys_##name(u64, u64, u64); \
    isize sys_##name(type0 arg0, type1 arg1, type2 arg2);

/* systask */
SYSCALL_DECLARE1(kill, tid_t, tid);
SYSCALL_DECLARE0(gettid);

/* sysdebug */
SYSCALL_DECLARE1(puts, const char*, str);
