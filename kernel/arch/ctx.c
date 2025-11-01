/*
 * context related definitions
 */

#include "kernel/arch/ctx.h"
#include "libs/assert.h"
#include "libs/log.h"
#include "libs/prelude.h"
#include "kernel/consts/params.h"
#include "kernel/mm/pm.h"
#include "kernel/mm/vm.h"
#include "kernel/mm/slab.h"
#include "kernel/arch/csr.h"
#include "kernel/trap.h"


// initialize a kernel context with given entry and newly allocated kernel stack
// caller should allocate memory for ctx
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
    kaddr_t kentry, 
    uaddr_t uentry
) {
    memset(actx, 0, sizeof(arch_ctx_t));

    actx->tf.sepc = uentry;
    actx->tf.sstatus = (r_sstatus() & ~SSTATUS_SPP) | SSTATUS_SPIE;
    actx->tf.ksp = mapped_kstack_top;
    actx->tf.x[2] = BIOS_BASE;

    ctx_init(&actx->ctx, kentry, mapped_kstack_top);
    
    unwrap_err(vm_alloc(
        vms,
        (vpn_t)PA2PN(mapped_kstack_top - KSTACK_SIZE),
        KSTACK_SIZE / PAGE_SIZE,
        VM_READ | VM_WRITE
    ));

    // guard page
    vm_map(
        vms,
        (vpn_t)PA2PN(mapped_kstack_top - KSTACK_SIZE) - 1,
        0,
        1,
        VM_READ | VM_WRITE | VM_FAKE
    );

    unwrap_err(vm_alloc(
        vms,
        (vpn_t)PA2PN(BIOS_BASE - USTACK_SIZE),
        USTACK_SIZE / PAGE_SIZE,
        VM_READ | VM_WRITE | VM_USER
    ));

    vm_map(
        vms,
        (vpn_t)PA2PN(BIOS_BASE - USTACK_SIZE) - 1,
        0,
        1,
        VM_READ | VM_WRITE | VM_USER | VM_FAKE
    );
}

void
actx_destroy(
    arch_ctx_t* actx,
    vm_space_t* vms
) {
    // free stacks and remove mappings
    // following logic is too tedious.
    // why not just add a parameter to vm_unmap, let's say, bool free_page?
    // idk. maybe for clearity of vm_unmap's purpose.

    vpn_t kvpn = (vpn_t)PA2PN(actx->tf.ksp) - (KSTACK_SIZE / PAGE_SIZE);
    vm_unmap(vms, kvpn - 1, 1);
    for (usize i = 0; i < KSTACK_SIZE / PAGE_SIZE; i++) {
        ppn_t ppn;
        assert(pgtbl_lookup(
            vms->pgtbl,
            kvpn,
            &ppn
        ));
        assert(pm_decref(ppn));
        vm_unmap(vms, kvpn, 1);
        kvpn += 1;
    }
    vpn_t uvpn = (vpn_t)PA2PN(BIOS_BASE - USTACK_SIZE);;
    vm_unmap(vms, uvpn - 1, 1);
    for (usize i = 0; i < USTACK_SIZE / PAGE_SIZE; i++) {
        ppn_t ppn;
        assert(pgtbl_lookup(
            vms->pgtbl,
            uvpn,
            &ppn
        ));
        assert(pm_decref(ppn));
        vm_unmap(vms, uvpn, 1);
        uvpn += 1;
    }    
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