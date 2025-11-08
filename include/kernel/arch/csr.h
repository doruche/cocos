/*
 * risc-v CSR accessors
 */
#pragma once

#include <libs/prelude.h>

#define impl_csr_access(csr) \
    static inline void \
    w_##csr(u64 x) { \
      asm volatile("csrw " #csr ", %0" : : "r" (x)); \
    } \
    static inline u64 \
    r_##csr() { \
      u64 x; \
      asm volatile("csrr %0, " #csr : "=r" (x) ); \
      return x; \
    }

impl_csr_access(stvec)
impl_csr_access(sstatus)
impl_csr_access(sscratch)
impl_csr_access(sie)
impl_csr_access(sepc)
impl_csr_access(scause)
impl_csr_access(stval)
impl_csr_access(satp)

#define STVEC_MODE_DIRECT 0
#define STVEC_MODE_VECTORED 1

#define STVEC(base, mode) (((base) & ~0x3) | ((mode) & 0x3))

static inline u64
rdtime() {
    u64 time;
    asm volatile("rdtime %0" : "=r" (time));
    return time;
}

/*
 * Indirect CSR accesses
 */

#define SSTATUS_SIE     (1L << 1)
#define SSTATUS_SPIE    (1L << 5)
#define SSTATUS_SPP     (1L << 8)
#define SSTATUS_SUM     (1L << 18)

#define SPP_USER       0
#define SPP_SUPERVISOR 1

#define SIE_SSIE        (1L << 1)
#define SIE_STIE        (1L << 5)
#define SIE_SEIE        (1L << 9)

#define SCAUSE_IRQ_FLAG    (1L << 63)
#define SCAUSE_IRQ_SOFT    1
#define SCAUSE_IRQ_TIMER   5
#define SCAUSE_IRQ_EXT     9
#define SCAUSE_EXC_INST_MISALIGNED  0
#define SCAUSE_EXC_INST_ACCESS      1
#define SCAUSE_EXC_ILLEGAL_INST     2
#define SCAUSE_EXC_BREAKPOINT       3
#define SCAUSE_EXC_LOAD_MISALIGNED  4
#define SCAUSE_EXC_LOAD_ACCESS      5
#define SCAUSE_EXC_STORE_MISALIGNED 6
#define SCAUSE_EXC_STORE_ACCESS     7
#define SCAUSE_EXC_ECALL_FROM_U     8
#define SCAUSE_EXC_ECALL_FROM_S     9
#define SCAUSE_EXC_INST_PAGE_FAULT  12
#define SCAUSE_EXC_LOAD_PAGE_FAULT  13
#define SCAUSE_EXC_STORE_PAGE_FAULT 15

static inline void
enable_intr() {
    w_sstatus(r_sstatus() | SSTATUS_SIE);
}

static inline void
disable_intr() {
    w_sstatus(r_sstatus() & ~SSTATUS_SIE);
}

static inline bool
intr_enabled() {
    return (r_sstatus() & SSTATUS_SIE) != 0;
}

static inline bool
scause_is_irq(u64 scause) {
    return (scause & SCAUSE_IRQ_FLAG) != 0;
}
