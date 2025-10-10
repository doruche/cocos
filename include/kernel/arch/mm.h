/*
 * riscv architecture specific definitions and macros
 */

#ifndef _K_ARCH_MM_H
#define _K_ARCH_MM_H 1

#include "libs/types.h"

#define PAGE_SIZE   0x1000
#define PAGE_SHIFT  12
#define PAGE_MASK   (PAGE_SIZE - 1)

#define PGUP(addr) (((addr) + PAGE_MASK) & ~PAGE_MASK)
#define PGDOWN(addr) ((addr) & ~PAGE_MASK)

#define PPN2PA(ppn) ((ppn) << PAGE_SHIFT)
#define PA2PPN(pa)  ((pa) >> PAGE_SHIFT)

// we use Sv39 mode
#define SATP_MODE_SV39 8
#define SATP(pgtbl) ((SATP_MODE_SV39 << 60) | (((u64)(pgtbl)) >> PAGE_SHIFT))

#define PTE_V   (1L << 0)   // valid
#define PTE_R   (1L << 1)   // readable
#define PTE_W   (1L << 2)   // writable
#define PTE_X   (1L << 3)   // executable
#define PTE_U   (1L << 4)   // user
#define PTE_G   (1L << 5)   // global
#define PTE_A   (1L << 6)   // accessed
#define PTE_D   (1L << 7)   // dirty

#define __user TAG(user)
#define __root TAG(root)

#ifndef __DEFONLY__

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
pte_t*  pgtbl_walk(pgtbl_t *pgtbl, vpn_t vpn, bool alloc);

#endif

#endif