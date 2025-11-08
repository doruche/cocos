#pragma once
#include "libs/prelude.h"

static inline result_t
arch_syscall(
    usize sysno,
    u64 arg0,
    u64 arg1,
    u64 arg2,
    u64 arg3,
    u64 arg4
) {
    register u64 a0 asm("a0") = arg0;
    register u64 a1 asm("a1") = arg1;
    register u64 a2 asm("a2") = arg2;
    register u64 a3 asm("a3") = arg3;
    register u64 a4 asm("a4") = arg4;
    register u64 a7 asm("a7") = sysno;
    asm volatile (
        "ecall"
        : "+r"(a0)
        : "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a7)
        : "memory"
    );
    return a0;
}