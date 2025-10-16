/*
 * context related definitions
 */

#ifndef _K_ARCH_CTX_H
#define _K_ARCH_CTX_H 1

#include "libs/types.h"

typedef struct _ctx_t {
    kaddr_t ra;
    kaddr_t sp;
    u64 s[12];
} ctx_t;

typedef struct _trapframe_t {
    u64 x[32];
    u64 sepc;
    u64 sstatus;
    u64 sscratch;
} trapframe_t;

typedef struct _arch_ctx_t {
    trapframe_t* tf;    // put this first for assembly access
    u64 scratch; // we put a scratch memory here for convienient access
    ctx_t ctx;
} arch_ctx_t;

void    ctx_init(ctx_t* ctx, void (*entry)(void), kaddr_t stack_top);
void    ctx_switch(ctx_t* prev, ctx_t* next);

void    arch_ctx_init(arch_ctx_t* actx, void (*entry)(void));
void    arch_ctx_destroy(arch_ctx_t* actx);

#endif