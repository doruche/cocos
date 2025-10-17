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


static kmem_cache_t arch_ctx_cache;

void
ctx_mm_init(void) {
    arch_ctx_cache = kmem_cache_create(sizeof(arch_ctx_t));
}

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
// will map: TRAMPOLINE, kstack, ustack
// as they are required for context switch and user program running
arch_ctx_t*
actx_init(
    vm_space_t* vms, // for setting up stack mappings
    kaddr_t mapped_kstack_top,
    kaddr_t entry, 
    uaddr_t sepc
) {
    arch_ctx_t* actx = (arch_ctx_t*)unwrap(kmem_cache_alloc(&arch_ctx_cache));
    memset(actx, 0, sizeof(arch_ctx_t));
    
    ppn_t ustack_bottom = unwrap(palloc(USTACK_SIZE / PAGE_SIZE));
    ppn_t kstack_bottom = unwrap(palloc(KSTACK_SIZE / PAGE_SIZE));

    actx->ustack_bottom = ustack_bottom;
    actx->kstack_bottom = kstack_bottom;

    actx->tf.sepc = sepc;
    actx->tf.sstatus = (r_sstatus() & ~SSTATUS_SPP) | SSTATUS_SPIE;
    actx->tf.sscratch = 0; // not used for now
    actx->tf.x[2] = BIOS_BASE;

    ctx_init(&actx->ctx, entry, mapped_kstack_top);
    
    vm_map(
        vms,
        (vpn_t)PA2PN(TRAMPOLINE),
        (ppn_t)PA2PN(TRAMPOLINE),
        1,
        VM_RESERVED, // trampoline should never be freed
        VM_EXEC | VM_READ
    );
    vm_map(
        vms,
        (vpn_t)((mapped_kstack_top - KSTACK_SIZE) / PAGE_SIZE),
        kstack_bottom,
        KSTACK_SIZE / PAGE_SIZE,
        VM_ALLOCATED,
        VM_READ | VM_WRITE | VM_CONTIGUOUS
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
        VM_READ | VM_WRITE | VM_USER | VM_CONTIGUOUS
    );
    vm_map(
        vms,
        (vpn_t)((BIOS_BASE - USTACK_SIZE) / PAGE_SIZE - 1),
        VM_FAKE_PPN,
        1,
        VM_RESERVED,
        VM_FAKE | VM_READ | VM_WRITE | VM_USER
    );
    return actx;
}

void
actx_destroy(arch_ctx_t* actx) {
    // if we map stacks as VM_ALLOCATED,
    // then they will be deallocated when destroying vm_space
    // if we map them as VM_RESERVED, we need to free them here
    // the option is actually arbitrary for now,
    // and we choose VM_ALLOCATED,
    // such that the only thing to do here is to free the actx itself
    kmem_cache_free(&arch_ctx_cache, actx);
}