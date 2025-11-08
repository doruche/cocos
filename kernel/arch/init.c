/*
 * architecture-specific initialization code.
 */

#include <libs/prelude.h>
#include <kernel/arch/arch.h>
#include <kernel/arch/csr.h>
#include <kernel/arch/qemu-virt.h>
#include <kernel/arch/trap.h>

static bootinfo_t bootinfo;

static void
clear_bss(void) {
    extern char __sbss[];
    extern char __ebss[];
    memset(__sbss, 0, (usize)(__ebss - __sbss));   
}

static void
platform_bootinfo_ctor(bootinfo_t* bootinfo) {
    extern u8 __bootimage[];
    bootinfo->bootimage = __bootimage;

    extern char __smem[];

    usize i = 0;

    bootinfo->zones[i].start = (u64)__smem;
    bootinfo->zones[i].end = PHYSTOP;
    bootinfo->zones[i++].type = MEMZONE_FREE;

    bootinfo->zones[i].start = PLIC;
    bootinfo->zones[i].end = PLIC + PLIC_RANGE;
    bootinfo->zones[i++].type = MEMZONE_DEV;

    bootinfo->zones[i].type = MEMZONE_NONE;
}

void
arch_init(void) {
    clear_bss();
    platform_bootinfo_ctor(&bootinfo);

    info("arch init...");

    disable_intr();
    w_sstatus(r_sstatus() | SPP_USER);
    w_sie(r_sie() & ~(SIE_SSIE | SIE_STIE | SIE_SEIE));
    w_stvec(STVEC((u64)ktrap_trampoline, STVEC_MODE_DIRECT));
    w_sstatus(r_sstatus() | SSTATUS_SUM);   // enable supervisor access user memory

    extern void kstart(bootinfo_t* bootinfo);
    kstart(&bootinfo);
}