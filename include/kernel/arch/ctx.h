/*
 * context related definitions
 */

#pragma once

#include "libs/types.h"
#include "kernel/mm/vm.h"
#include "kernel/arch/board.h"

#define TRAMPOLINE  (VIRSTOP - PAGE_SIZE)

typedef struct _ctx_t {
    kaddr_t ra;
    kaddr_t sp;
    u64     s[12];
} ctx_t;

typedef struct _trapframe_t {
    // asm & c access
    u64     x[32];
    __readonly kaddr_t ksp; // kernel sp, will not change after initialized

    // c access
    uaddr_t sepc;
    u64     sstatus;
} trapframe_t;

typedef struct _arch_ctx_t {
    trapframe_t tf;    // put this first for assembly access
    ctx_t ctx;
} arch_ctx_t;

void        ctx_init(ctx_t* ctx, kaddr_t entry, kaddr_t mapped_stack_top);
void        ctx_switch(ctx_t* prev, ctx_t* next);

void        actx_init(
    arch_ctx_t* actx,
    vm_space_t* vms, 
    kaddr_t mapped_kstack_top, 
    kaddr_t kentry, 
    uaddr_t uentry
);
void        actx_destroy(arch_ctx_t* actx, vm_space_t* vms);
void        actx_utrap_entry(arch_ctx_t* cur_actx);
void        actx_utrap_ret(arch_ctx_t* cur_actx);