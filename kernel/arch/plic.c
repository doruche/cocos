#include <kernel/arch/arch.h>
#include <kernel/arch/plic.h>
#include <kernel/arch/qemu-virt.h>

void
arch_irq_enable(irq_t irqno) {
    assert(irqno < IRQ_MAX);

    *(volatile u32*)PLIC_PRIORITY(irqno) = 1;
    *(volatile u32*)PLIC_SENABLE(0, irqno) = 
        *(volatile u32*)PLIC_SENABLE(0, irqno) | (1 << irqno % 32);
}

void
arch_irq_disable(irq_t irqno) {
    assert(irqno < IRQ_MAX);

    *(volatile u32*)PLIC_PRIORITY(irqno) = 0;
    *(volatile u32*)PLIC_SENABLE(0, irqno) = 
        *(volatile u32*)PLIC_SENABLE(0, irqno) & ~(1 << irqno % 32);
}

void
plic_init(void) {
    *(volatile u32*)PLIC_STHRESHOLD(0) = 0;
}

irq_t
plic_claim(void) {
    return *(volatile u32*)PLIC_SCLAIM(0);
}

void
plic_complete(irq_t irqno) {
    assert(irqno < IRQ_MAX);
    *(volatile u32*)PLIC_SCOMPLETE(0) = irqno;
}