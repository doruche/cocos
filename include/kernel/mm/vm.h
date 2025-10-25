/*
 * virtual memory management
 */
#pragma once

#include "libs/types.h"
#include "libs/list.h"
#include "kernel/arch/mm.h"
#include "kernel/boot.h"

typedef struct _vm_space_t {
    pgtbl_t* pgtbl;
} vm_space_t;

void        vm_init(vm_space_t* vms);
void        vm_destroy(vm_space_t* vms);
void        vm_map(
    vm_space_t* vms, 
    vpn_t vpn, 
    ppn_t ppn,
    usize npages,
    vm_flags_t flags
);
void        vm_unmap(
    vm_space_t* vms, 
    vpn_t vpn, 
    usize npages
);
void        vm_grant(
    vm_space_t* dst,
    vm_space_t* src,
    vpn_t from,
    vpn_t to,
    usize npages,
    vm_flags_t flags
);
isize       vm_alloc(
    vm_space_t* vms,
    vpn_t vpn,
    usize npages,
    vm_flags_t flags
);

typedef void (*vm_iter_callback_t)(
    vaddr_t vaddr,
    paddr_t paddr,
    usize len,
    void* ctx
);
isize       vm_iter(
    vm_space_t* vms,
    vaddr_t start,
    usize n,
    vm_iter_callback_t callback,
    void* ctx
);
isize       vm_memcpy(
    vm_space_t* vms,
    vaddr_t dst,
    kaddr_t src,
    usize n
);
isize       vm_memset(
    vm_space_t* vms,
    vaddr_t dst,
    u8 value,
    usize n
);

void        vm_activate(vm_space_t* vms);
bool        vm_is_mapped(vm_space_t* vms, vpn_t vpn);

void        kvms_init(bootinfo_t* bootinfo);
void        kvms_derive(vm_space_t* vms);

void        vm_dump(vm_space_t* vms);

static inline bool
pte_is_leaf(pte_t pte) {
    return (pte & (PTE_R | PTE_W | PTE_X)) != 0 && (pte & PTE_V) != 0;
}

static inline bool
pte_is_branch(pte_t pte) {
    return (pte & (PTE_R | PTE_W | PTE_X)) == 0 && (pte & PTE_V) != 0;
}

static inline bool
pte_is_mapped(pte_t pte) {
    return (pte & (PTE_R | PTE_W | PTE_X | PTE_V)) != 0; // include fake mappings
}
