/*
 * architecture-specific initialization code.
 */

#include "kernel/misc/log.h"
#include "kernel/boot.h"
#include "kernel/arch/csr.h"
#include "kernel/trap.h"
#include "kernel/arch/init.h"
#include "kernel/misc/assert.h"
#include "kernel/arch/board.h"

static bootinfo_t bootinfo;

static void
bootinfo_ctor(void) {
    // currently hardcoded.
    extern char __ekern[];
    extern char __smem[];

    bootinfo.zones[0].start = KERN_BASE;
    bootinfo.zones[0].end = (u64)__ekern;
    bootinfo.zones[0].type = MEMZONE_KERNEL;

    bootinfo.zones[1].start = (u64)__smem;
    bootinfo.zones[1].end = PHYSTOP;
    bootinfo.zones[1].type = MEMZONE_FREE;

    bootinfo.zones[2].start = UART0;
    bootinfo.zones[2].end = UART0 + UART0_RANGE;
    bootinfo.zones[2].type = MEMZONE_DEV;

    bootinfo.zones[3].start = PLIC;
    bootinfo.zones[3].end = PLIC + PLIC_RANGE;
    bootinfo.zones[3].type = MEMZONE_DEV;

    bootinfo.zones[4].start = VIRTIO0;
    bootinfo.zones[4].end = VIRTIO0 + VIRTIO0_RANGE;
    bootinfo.zones[4].type = MEMZONE_DEV;

    bootinfo.zones[5].type = MEMZONE_NONE;
}

void
arch_init(void) {
    info("arch init...");

    disable_intr();
    w_sstatus(r_sstatus() | SPP_USER);
    w_sie(r_sie() & ~(SIE_SSIE | SIE_STIE | SIE_SEIE));
    w_stvec(STVEC((u64)ktrap_trampoline, STVEC_MODE_DIRECT));
    info("interrupt done.");

    bootinfo_ctor();
    info("bootinfo constructed.");

    kstart(&bootinfo);
}