#pragma once
#include "libs/types.h"

static inline u64
arch_syscall(
    usize sysno,
    u64 arg0,
    u64 arg1,
    u64 arg2
) {
    // register u64 a0 asm ("a0") = arg0;
    // register u64 a1 asm ("a1") = arg1;
    // register u64 a2 asm ("a2") = arg2;
    // register u64 a7 asm ("a7") = sysno;
    u64 result;
    asm volatile (
        "mv a0, %1\n"
        "mv a1, %2\n"
        "mv a2, %3\n"
        "mv a7, %4\n"
        "ecall"
        : "=r"(result)
        : "r"(arg0), "r"(arg1), "r"(arg2), "r"(sysno)
        : "a0", "a1", "a2", "a7", "memory"
    );
    return result;
}