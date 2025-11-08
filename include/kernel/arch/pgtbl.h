/*
 * we only support Sv39 page table format
 */

#pragma once

#include <libs/prelude.h>

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

#define PTE_S1      (1L << 8)   // software defined
#define PTE_ANON    PTE_S1     // anonymous mapping

#define PTE2PA(pte) (((pte) >> 10) << PAGE_SHIFT)
#define PTE2PPN(pte) ((pte) >> 10)

#define PTE_FLAGS(pte) ((pte) & 0x3FF)

static inline void
flush_tlb() {
    asm volatile("sfence.vma zero, zero");
}

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

static inline bool
pte_is_anonymous(pte_t pte) {
    return (pte & PTE_ANON) != 0;
}