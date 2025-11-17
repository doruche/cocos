/*
 * syscall handler interface.
 */

#pragma once

#include <libs/prelude.h>
#include <kernel/arch/arch.h>
#include <kernel/task/sched.h>
#include <kernel/task/processor.h>

typedef u64 (*syscall_ptr_t)(
    u64, u64, u64, u64, u64
);

result_t    syscall_dispatch(
    u64 syscall_no, 
    arch_trapframe_t* tf
);

/* helpers */

#define SYSCALL_DEFINE0(name) \
    u64 __sys_##name( \
        u64 __arg0, u64 __arg1, u64 __arg2, u64 __arg3, u64 __arg4 \
    ) { \
        return sys_##name(); \
    } \
    result_t sys_##name(void)
#define SYSCALL_DECLARE0(name) \
    u64 __sys_##name(u64, u64, u64, u64, u64); \
    result_t sys_##name(void);

#define SYSCALL_DEFINE1(name, type0, arg0) \
    u64 __sys_##name( \
        u64 __arg0, u64 __arg1, u64 __arg2, u64 __arg3, u64 __arg4 \
    ) { \
        type0 arg0 = (type0)__arg0; \
        return (u64)sys_##name(arg0); \
    } \
    result_t sys_##name(type0 arg0)
#define SYSCALL_DECLARE1(name, type0, arg0) \
    u64 __sys_##name(u64, u64, u64, u64, u64); \
    result_t sys_##name(type0 arg0);

#define SYSCALL_DEFINE2(name, type0, arg0, type1, arg1) \
    u64 __sys_##name( \
        u64 __arg0, u64 __arg1, u64 __arg2, u64 __arg3, u64 __arg4 \
    ) { \
        type0 arg0 = (type0)__arg0; \
        type1 arg1 = (type1)__arg1; \
        return sys_##name(arg0, arg1); \
    } \
    result_t sys_##name(type0 arg0, type1 arg1)
#define SYSCALL_DECLARE2(name, type0, arg0, type1, arg1) \
    u64 __sys_##name(u64, u64, u64, u64, u64); \
    result_t sys_##name(type0 arg0, type1 arg1);

#define SYSCALL_DEFINE3(name, type0, arg0, type1, arg1, type2, arg2) \
    u64 __sys_##name( \
        u64 __arg0, u64 __arg1, u64 __arg2, u64 __arg3, u64 __arg4 \
    ) { \
        type0 arg0 = (type0)__arg0; \
        type1 arg1 = (type1)__arg1; \
        type2 arg2 = (type2)__arg2; \
        return sys_##name(arg0, arg1, arg2); \
    } \
    result_t sys_##name(type0 arg0, type1 arg1, type2 arg2)
#define SYSCALL_DECLARE3(name, type0, arg0, type1, arg1, type2, arg2) \
    u64 __sys_##name(u64, u64, u64, u64, u64); \
    result_t sys_##name(type0 arg0, type1 arg1, type2 arg2);

#define SYSCALL_DEFINE4(name, type0, arg0, type1, arg1, type2, arg2, type3, arg3) \
    u64 __sys_##name( \
        u64 __arg0, u64 __arg1, u64 __arg2, u64 __arg3, u64 __arg4 \
    ) { \
        type0 arg0 = (type0)__arg0; \
        type1 arg1 = (type1)__arg1; \
        type2 arg2 = (type2)__arg2; \
        type3 arg3 = (type3)__arg3; \
        return sys_##name(arg0, arg1, arg2, arg3); \
    } \
    result_t sys_##name(type0 arg0, type1 arg1, type2 arg2, type3 arg3)
#define SYSCALL_DECLARE4(name, type0, arg0, type1, arg1, type2, arg2, type3, arg3) \
    u64 __sys_##name(u64, u64, u64, u64, u64); \
    result_t sys_##name(type0 arg0, type1 arg1, type2 arg2, type3 arg3);

#define SYSCALL_DEFINE5(name, type0, arg0, type1, arg1, type2, arg2, type3, arg3, type4, arg4) \
    u64 __sys_##name( \
        u64 __arg0, u64 __arg1, u64 __arg2, u64 __arg3, u64 __arg4 \
    ) { \
        type0 arg0 = (type0)__arg0; \
        type1 arg1 = (type1)__arg1; \
        type2 arg2 = (type2)__arg2; \
        type3 arg3 = (type3)__arg3; \
        type4 arg4 = (type4)__arg4; \
        return sys_##name(arg0, arg1, arg2, arg3, arg4); \
    } \
    result_t sys_##name(type0 arg0, type1 arg1, type2 arg2, type3 arg3, type4 arg4)
#define SYSCALL_DECLARE5(name, type0, arg0, type1, arg1, type2, arg2, type3, arg3, type4, arg4) \
    u64 __sys_##name(u64, u64, u64, u64, u64); \
    result_t sys_##name(type0 arg0, type1 arg1, type2 arg2, type3 arg3, type4 arg4);

/* task */
SYSCALL_DECLARE1(task_destroy, tid_t, tid);
SYSCALL_DECLARE0(task_gettid);
SYSCALL_DECLARE3(
    task_spawn, 
    const char*, name, 
    uaddr_t, entry, 
    asid_t, asid
);
SYSCALL_DECLARE0(task_yield);
SYSCALL_DECLARE1(task_block, tid_t, tid);
SYSCALL_DECLARE1(task_resume, tid_t, tid);
SYSCALL_DECLARE1(task_exit, result_t, exit_code);
SYSCALL_DECLARE1(task_getzombie, zombie_task_t*, out);

/* irq */
SYSCALL_DECLARE1(irq_listen, irq_t, irqno);
SYSCALL_DECLARE1(irq_unlisten, irq_t, irqno);

/* ipc */
SYSCALL_DECLARE4(
    ipc,
    tid_t, send_to,
    tid_t, recv_from,
    msg_t*, msg,
    ipc_flags_t, flags
);
SYSCALL_DECLARE2(
    notify,
    tid_t, dst,
    notif_t, notifs
);

/* as */
SYSCALL_DECLARE1(as_get, tid_t, tid);
SYSCALL_DECLARE5(
    as_map,
    asid_t, asid,
    vpn_t, vpn,
    ppn_t, ppn,
    usize, npages,
    vm_flags_t, flags
);
SYSCALL_DECLARE3(
    as_unmap,
    asid_t, asid,
    vpn_t, vpn,
    usize, npages
);
SYSCALL_DECLARE4(
    as_memcpy,
    asid_t, asid,
    vaddr_t, addr,
    const u8*, buf,
    usize, len
);
SYSCALL_DECLARE4(
    as_memset,
    asid_t, asid,
    vaddr_t, addr,
    u8, value,
    usize, len
);

/* dbg */
SYSCALL_DECLARE2(
    dbg_puts, 
    const char*, str,
    usize, len
);
