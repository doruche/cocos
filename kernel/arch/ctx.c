/*
 * context related definitions
 */

#include "kernel/arch/ctx.h"
#include "kernel/misc/assert.h"
#include "libs/macros.h"
#include "kernel/misc/log.h"
#include "libs/types.h"

void
ctx_init(ctx_t* ctx, void (*entry)(void), u64 stack_top) {
    assert(ctx != NULL);
    ctx->ra = (u64)entry;
    ctx->sp = stack_top;
    for (int i = 0; i < 12; i++) {
        ctx->s[i] = 0;
    }
}

void
ctx_switch(ctx_t* prev, ctx_t* next) {
    assert(prev != NULL && next != NULL);
    assert_ne(prev, next);

    extern void
    __ctx_switch(ctx_t* prev, ctx_t* next);

    __ctx_switch(prev, next);
}