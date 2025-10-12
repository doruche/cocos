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
#include "kernel/arch/mm.h"

static bootinfo_t bootinfo;

static void
bootinfo_ctor(void) {
    // currently hardcoded.
    extern char __etext[];
    extern char __srodata[];
    extern char __erodata[];
    extern char __sdata[];
    extern char __edata[];
    extern char __sbss[];
    extern char __ebss[];
    extern char __boot_stacks_bottom[];
    extern char __boot_stacks_top[];
    extern char __smem[];

    usize i = 0;

    bootinfo.zones[i].start = KERN_BASE;
    bootinfo.zones[i].end = PGUP((u64)__etext);
    bootinfo.zones[i++].type = MEMZONE_K_TEXT;

    bootinfo.zones[i].start = (u64)__srodata;
    bootinfo.zones[i].end = PGUP((u64)__erodata);
    bootinfo.zones[i++].type = MEMZONE_K_RODATA;

    bootinfo.zones[i].start = (u64)__sdata;
    bootinfo.zones[i].end = PGUP((u64)__edata);
    bootinfo.zones[i++].type = MEMZONE_K_DATA;

    bootinfo.zones[i].start = (u64)__sbss;
    bootinfo.zones[i].end = PGUP((u64)__ebss);
    bootinfo.zones[i++].type = MEMZONE_K_BSS;

    bootinfo.zones[i].start = PGUP((u64)__boot_stacks_bottom);
    bootinfo.zones[i].end = PGUP((u64)__boot_stacks_top);
    bootinfo.zones[i++].type = MEMZONE_K_BSS; // treat stacks as bss, cz they can be written to

    bootinfo.zones[i].start = (u64)__smem;
    bootinfo.zones[i].end = PHYSTOP;
    bootinfo.zones[i++].type = MEMZONE_FREE;

    bootinfo.zones[i].start = UART0;
    bootinfo.zones[i].end = UART0 + UART0_RANGE;
    bootinfo.zones[i++].type = MEMZONE_DEV;

    bootinfo.zones[i].start = PLIC;
    bootinfo.zones[i].end = PLIC + PLIC_RANGE;
    bootinfo.zones[i++].type = MEMZONE_DEV;

    bootinfo.zones[i].start = VIRTIO0;
    bootinfo.zones[i].end = VIRTIO0 + VIRTIO0_RANGE;
    bootinfo.zones[i++].type = MEMZONE_DEV;

    bootinfo.zones[i].type = MEMZONE_NONE;
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