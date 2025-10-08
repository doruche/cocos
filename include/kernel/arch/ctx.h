/*
 * context related definitions
 */

#ifndef _K_ARCH_CTX_H
#define _K_ARCH_CTX_H 1

#include "libs/types.h"

typedef struct _ctx_t {
    u64 ra;
    u64 sp;
    u64 s[12];
} ctx_t;

void    ctx_init(ctx_t* ctx, void (*entry)(void), u64 stack_top);
void    ctx_switch(ctx_t* prev, ctx_t* next);

#endif