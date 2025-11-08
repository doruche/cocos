/*
 * Architecture-independent definitions.
 * Other parts of the kernel should include this file instead of
 * including architecture-specific headers directly.
 * 
 * Actually only riscv64 is supported in this teaching kernel,
 * but it is necessary to separate architecture-independent code
 * from architecture-specific code for both readability and cleanliness.
 */

#pragma once

#include <libs/prelude.h>

/*
 * Note that other parts of the kernel should not directly
 * access fields of these structures. Use the provided
 * functions instead.
 * We could just declare these structs in arch.h and
 * define them in arch-specific headers, but for simplicity
 * we define them here directly.
 */

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

#define NMEMZONE_MAX    8

enum memzone_type {
    MEMZONE_FREE,
    MEMZONE_DEV,
    MEMZONE_NONE,
};

typedef struct _memzone_t {
    u64 start;
    u64 end;
    enum memzone_type type;
} memzone_t;

typedef struct _bootinfo_t {
    u8* bootimage;
    memzone_t zones[NMEMZONE_MAX];
    usize frequency_hz;
} bootinfo_t;

/*
 * Note that no error reporting should exist in arch layer,
 * as arch layer functions are expected to be called
 * by higher-level kernel code which can handle errors properly.
 * If an unrecoverable error occurs, arch layer functions
 * should just panic.
 */

void    arch_init(void);

void    arch_dbg_write(char c);

void    arch_timer_init(void);
void    arch_timer_set(u64 timecmp);
u64     arch_timer_get(void);

void    arch_intr_set(bool enable);
bool    arch_intr_status(void);
void    arch_intr_wait(void);
void    arch_irq_enable(u8 irq);
void    arch_irq_disable(u8 irq);

u64     arch_syscall_arg(
    arch_trapframe_t* tf,
    usize idx
);
void    arch_store_syscall_ret(
    arch_trapframe_t* tf,
    isize ret
);
void    arch_set_pc(
    arch_trapframe_t* tf,
    uaddr_t pc
);

void    arch_ctx_init(
    arch_ctx_t* ctx,
    arch_vm_t* vm,
    kaddr_t kentry,
    uaddr_t uentry,
    vpn_t kstack_top
);
void    arch_ctx_destroy(
    arch_ctx_t* actx,
    arch_vm_t* vm
);
arch_kctx_t* arch_ctx_kctx(arch_ctx_t* ctx);
void    arch_kctx_init(
    arch_kctx_t* kctx,
    kaddr_t entry,
    vpn_t kstack_top
);
void    arch_kctx_load(arch_kctx_t* kctx);
void    arch_kctx_switch(arch_kctx_t* prev, arch_kctx_t* next);
void    arch_utrap_ret(void);


// vm flags defined in libs/prelude.h
arch_vm_t* arch_vm_creat(void);
void    arch_vm_activate(arch_vm_t* vm);
void    arch_vm_deactivate(void);
void    arch_vm_destroy(arch_vm_t* vm);
void    arch_vm_map(
    arch_vm_t* vm,
    vpn_t vpn,
    ppn_t ppn,
    vm_flags_t flags
);
void    arch_vm_unmap(arch_vm_t* vm, vpn_t vpn);
ppn_t   arch_vm_resolve(arch_vm_t* vm, vpn_t vpn);
// whether the given vpn is mapped in the given vm
bool    arch_vm_is_mapped(arch_vm_t* vm, vpn_t vpn);
/*
 * stricter than arch_vm_is_mapped.
 * if the vpn is mapped or belongs to a special region (e.g. TRAMPOLINE),
 * return false. otherwise return true.
 */
bool    arch_vm_is_mappable(arch_vm_t* vm, vpn_t vpn);
void    arch_vm_flush_tlb(void);
void    arch_kvm_init(void);

vpn_t   arch_vm_topaddr(void);
vpn_t   arch_vm_kbase(void);

void    arch_shutdown(void);

