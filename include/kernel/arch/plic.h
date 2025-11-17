#pragma once

#include <libs/prelude.h>
#include <kernel/arch/qemu-virt.h>

/*
 * OpenSBI has already initialized PLIC in m-mode and
 * delegated external interrupts to s-mode.
 * So here we only need to deal with s-mode PLIC settings.
 */

/* 
 * See
 * https://github.com/riscv/riscv-plic-spec/blob/master/riscv-plic.adoc 
 * for details.
 */

#define PLIC_PRIORITY(irq) \
    (PLIC + (irq) * sizeof(u32))
#define PLIC_SENABLE(hart, irq) \
    (PLIC + 0x2080 + (hart) * 0x100 + ((irq) / 32 * sizeof(u32)))
#define PLIC_STHRESHOLD(hart) \
    (PLIC + 0x201000 + (hart) * 0x2000)
#define PLIC_SCOMPLETE(hart) \
    (PLIC + 0x201004 + (hart) * 0x2000)
#define PLIC_SCLAIM(hart) PLIC_SCOMPLETE(hart)

void plic_init(void);
irq_t plic_claim(void);
void plic_complete(irq_t irqno);