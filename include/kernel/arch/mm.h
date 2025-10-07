/*
 * riscv architecture specific definitions and macros
 */

#ifndef _K_ARCH_RISCV_H
#define _K_ARCH_RISCV_H 1

#define PAGE_SIZE   0x1000
#define PAGE_SHIFT  12
#define PAGE_MASK   (PAGE_SIZE - 1)

#define PGUP(addr) (((addr) + PAGE_MASK) & ~PAGE_MASK)
#define PGDOWN(addr) ((addr) & ~PAGE_MASK)

// we use Sv39 mode
#define SATP_MODE_SV39 8
#define SATP(pgtbl) ((SATP_MODE_SV39 << 60) | (((u64)(pgtbl)) >> PAGE_SHIFT))

#ifndef __DEFONLY__

static inline void
flush_tlb() {
    asm volatile("sfence.vma zero, zero");
}

#endif

#endif // !_K_ARCH_RISCV_H