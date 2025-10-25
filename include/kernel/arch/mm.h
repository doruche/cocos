/*
 * riscv architecture specific definitions and macros
 */

#pragma once

#include "libs/types.h"
#include "libs/macros.h"
#include "kernel/mm/pm.h"

// we use Sv39 mode
#define SATP_MODE_SV39 8L
#define SATP(pgtbl) ((SATP_MODE_SV39 << 60) | (((u64)(pgtbl)) >> PAGE_SHIFT))

#define PTE_V   (1L << 0)   // valid
#define PTE_R   (1L << 1)   // readable
#define PTE_W   (1L << 2)   // writable
#define PTE_X   (1L << 3)   // executable
#define PTE_U   (1L << 4)   // user
#define PTE_G   (1L << 5)   // global
#define PTE_A   (1L << 6)   // accessed
#define PTE_D   (1L << 7)   // dirty

#define PTE2PA(pte) (((pte) >> 10) << PAGE_SHIFT)
#define PTE2PPN(pte) ((pte) >> 10)

#define PTE_FLAGS(pte) ((pte) & 0x3FF)

static inline void
flush_tlb() {
    asm volatile("sfence.vma zero, zero");
}

typedef u64 pte_t;

typedef struct _pgtbl_t {
    pte_t entries[512];
} pgtbl_t;

void    pgtbl_init(pgtbl_t* pgtbl);
void    pgtbl_destroy(pgtbl_t* pgtbl);
void    pgtbl_map(pgtbl_t *pgtbl, vpn_t vpn, ppn_t ppn, u64 flags);
void    pgtbl_unmap(pgtbl_t *pgtbl, vpn_t vpn);
bool    pgtbl_lookup(pgtbl_t* pgtbl, vpn_t vpn, ppn_t* out_ppn);
void    pgtbl_activate(pgtbl_t *pgtbl);

vm_flags_t pte_archflag2vmflag(u64 flags);
u64 pte_vmflag2archflag(vm_flags_t flags);

typedef void  (*pgtbl_leaf_walker)(
    pgtbl_t *pgtbl, 
    vpn_t vpn,
    pte_t* pte,
    void* ctx
);
typedef void (*pgtbl_branch_walker)(
    pgtbl_t *pgtbl, 
    pte_t* pte,
    void* ctx
);
void    pgtbl_walk(
    pgtbl_t *pgtbl, 
    pgtbl_leaf_walker leaf,
    pgtbl_branch_walker branch,
    void* ctx
);
void generic_branch_unmapper(
    pgtbl_t *pgtbl, 
    pte_t* pte,
    void* ctx
);


void    pgtbl_dump(pgtbl_t *pgtbl);
