#pragma once

#include <libs/prelude.h>
#include <kernel/arch/arch.h>

typedef struct _arch_kctx_t {
    kaddr_t ra;
    kaddr_t sp;
    u64     s[12];
} arch_kctx_t;

typedef struct _arch_trapframe_t {
    // asm & c access
    u64     x[32]; 
    // kernel sp, will not change after initialized
    __readonly kaddr_t ksp;

    // c access
    uaddr_t sepc;
    u64     sstatus;
} arch_trapframe_t;

typedef struct _arch_ctx_t {
    // put this first for assembly access
    arch_trapframe_t tf; 
    arch_kctx_t kctx;
} arch_ctx_t;

typedef struct _arch_vm_t {
    // page table entries
    pte_t entries[512];
} arch_vm_t;

