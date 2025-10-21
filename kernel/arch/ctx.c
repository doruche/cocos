/*
 * context related definitions
 */

#include "kernel/arch/ctx.h"
#include "kernel/misc/assert.h"
#include "libs/macros.h"
#include "kernel/misc/log.h"
#include "libs/types.h"
#include "kernel/consts/params.h"
#include "libs/string.h"
#include "kernel/mm/pm.h"
#include "kernel/mm/vm.h"
#include "kernel/mm/slab.h"
#include "kernel/arch/csr.h"
#include "kernel/trap.h"


// initialize a kernel context with given entry and newly allocated kernel stack
// caller should allocate memory for ctx
// one exception: in arch_ctx_init, we allocate ctx_t in arch_ctx_t from slab
void
ctx_init(ctx_t* ctx, kaddr_t entry, kaddr_t mapped_stack_top) {
    ctx->ra = entry;
    assert(is_aligned(mapped_stack_top, PAGE_SIZE));
    ctx->sp = mapped_stack_top;
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

// vms required here to setup k/ustack mappings
// as they are required for context switch and user program running
// WILL ALLOCATE MEMORY FOR STACKS!!!
void
actx_init(
    arch_ctx_t* actx,
    vm_space_t* vms, // for setting up stack mappings
    kaddr_t mapped_kstack_top,
    kaddr_t entry, 
    uaddr_t sepc
) {
    memset(actx, 0, sizeof(arch_ctx_t));
    
    ppn_t ustack_bottom = unwrap_err(palloc(USTACK_SIZE / PAGE_SIZE));
    ppn_t kstack_bottom = unwrap_err(palloc(KSTACK_SIZE / PAGE_SIZE));

    actx->ustack_bottom = ustack_bottom;
    actx->kstack_bottom = kstack_bottom;

    actx->tf.sepc = sepc;
    actx->tf.sstatus = (r_sstatus() & ~SSTATUS_SPP) | SSTATUS_SPIE;
    actx->tf.ksp = mapped_kstack_top;
    actx->tf.x[2] = BIOS_BASE;

    ctx_init(&actx->ctx, entry, mapped_kstack_top);
    
    vm_map(
        vms,
        (vpn_t)((mapped_kstack_top - KSTACK_SIZE) / PAGE_SIZE),
        kstack_bottom,
        KSTACK_SIZE / PAGE_SIZE,
        VM_ALLOCATED,
        VM_READ | VM_WRITE
    );
    vm_map(
        vms,
        (vpn_t)((mapped_kstack_top - KSTACK_SIZE) / PAGE_SIZE - 1),
        VM_FAKE_PPN,
        1,
        VM_RESERVED,
        VM_FAKE | VM_READ | VM_WRITE
    );
    vm_map(
        vms,
        (vpn_t)((BIOS_BASE - USTACK_SIZE) / PAGE_SIZE),
        ustack_bottom,
        USTACK_SIZE / PAGE_SIZE,
        VM_ALLOCATED,
        VM_READ | VM_WRITE | VM_USER
    );
    vm_map(
        vms,
        (vpn_t)((BIOS_BASE - USTACK_SIZE) / PAGE_SIZE - 1),
        VM_FAKE_PPN,
        1,
        VM_RESERVED,
        VM_FAKE | VM_READ | VM_WRITE | VM_USER
    );
}

void
actx_utrap_entry(arch_ctx_t* cur_actx) {
    // gprs & sscratch already stored by asm code
    cur_actx->tf.sstatus = r_sstatus();
    cur_actx->tf.sepc = r_sepc();
    w_stvec(STVEC((u64)ktrap_trampoline, STVEC_MODE_DIRECT));
    enable_intr();
}

void
actx_utrap_ret(arch_ctx_t* cur_actx) {
    disable_intr();
    w_sscratch((u64)cur_actx);
    w_sepc(cur_actx->tf.sepc);
    w_sstatus((cur_actx->tf.sstatus & ~SSTATUS_SPP) | SSTATUS_SPIE);
    w_stvec(STVEC(TRAMPOLINE, STVEC_MODE_DIRECT));  
}