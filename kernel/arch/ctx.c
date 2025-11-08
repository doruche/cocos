/*
 * context related definitions
 */

#include <libs/prelude.h>
#include <kernel/arch/arch.h>
#include <kernel/arch/csr.h>
#include <kernel/arch/trap.h>
#include <kernel/arch/qemu-virt.h>
#include <kernel/consts/params.h>
#include <kernel/mm/pm.h>

void
arch_kctx_init(
    arch_kctx_t* kctx, 
    kaddr_t entry, 
    vpn_t kstack_top
) {
    kctx->ra = entry;
    kctx->sp = PN2PA(kstack_top);
    for (int i = 0; i < 12; i++) {
        kctx->s[i] = 0;
    }
}

void
arch_kctx_load(
    arch_kctx_t* kctx
) {
    extern void
    __kctx_switch(arch_kctx_t* prev, arch_kctx_t* next);
    static arch_kctx_t placeholder;
    
    __kctx_switch(&placeholder, kctx);
}

void
arch_kctx_switch(
    arch_kctx_t* prev, 
    arch_kctx_t* next
) {
    extern void
    __kctx_switch(arch_kctx_t* prev, arch_kctx_t* next);

    __kctx_switch(prev, next);
}

/*
 * initialize an architecture-specific context
 * for a new task. both user trapframe and
 * kernel context.
 * TODO: we should not set up user stack here,
 * as user stack allocation is the responsibility
 * of process manager. refine later.
 */
void
arch_ctx_init(
    arch_ctx_t* ctx,
    arch_vm_t* vm,
    kaddr_t kentry, 
    uaddr_t uentry,
    vpn_t kstack_top
) {
    memset(ctx, 0, sizeof(arch_ctx_t));
    
    arch_kctx_init(&ctx->kctx, kentry, kstack_top);
    ctx->tf.sepc = uentry;
    ctx->tf.sstatus = (r_sstatus() & ~SSTATUS_SPP) | SSTATUS_SPIE;
    ctx->tf.ksp = PN2PA(kstack_top);
    ctx->tf.x[2] = BIOS_BASE;

    // allocate and map kernel stack
    for (usize i = 0; i < KSTACK_SIZE / PAGE_SIZE; i++) {
        arch_vm_map(
            vm,
            (vpn_t)(kstack_top - KSTACK_SIZE / PAGE_SIZE + i),
            PPN_ANON,
            VM_READ | VM_WRITE | VM_ANON
        );
    }
    // guard page
    arch_vm_map(
        vm,
        (vpn_t)(kstack_top - KSTACK_SIZE / PAGE_SIZE - 1),
        0,
        VM_READ | VM_WRITE | VM_FAKE
    );

    // allocate and map user stack
    for (usize i = 0; i < USTACK_SIZE / PAGE_SIZE; i++) {
        arch_vm_map(
            vm,
            (vpn_t)(BIOS_BASE / PAGE_SIZE - USTACK_SIZE / PAGE_SIZE + i),
            PPN_ANON,
            VM_USER | VM_READ | VM_WRITE | VM_ANON
        );
    }
    arch_vm_map(
        vm,
        (vpn_t)(BIOS_BASE / PAGE_SIZE - USTACK_SIZE / PAGE_SIZE - 1),
        0,
        VM_USER | VM_READ | VM_WRITE | VM_FAKE
    );
}

void
arch_ctx_destroy(
    arch_ctx_t* actx,
    arch_vm_t* vm
) {
    // currently nothing to do here
    // user memory will be freed when addr_space_t is destroyed
    // however if we want to extend our design to support threads,
    // we may need to unmap and free those kernel stacks here
    // immediately when a thread is destroyed.
    trace("arch_ctx_destroy: called");
}

arch_kctx_t*
arch_ctx_kctx(arch_ctx_t* ctx) {
    return &ctx->kctx;
}

void
arch_intr_set(bool enable) {
    if (enable) {
        enable_intr();
    } else {
        disable_intr();
    }
}

bool
arch_intr_status(void) {
    return intr_enabled();
}

