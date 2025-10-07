/*
 * architecture-specific initialization code.
 */

#include "kernel/misc/log.h"
#include "kernel/boot.h"
#include "kernel/arch/csr.h"


void
arch_init(void) {
    info("arch_init: nothing to do for now");

    info("sstatus: 0x%lx", r_sstatus());
    info("stvec: 0x%lx", r_stvec());
    info("sscratch: 0x%lx", r_sscratch());
    info("sepc: 0x%lx", r_sepc());
    info("scause: 0x%lx", r_scause());
    info("stval: 0x%lx", r_stval());
    info("time: 0x%lx", rdtime());

    disable_intr();
    w_sstatus(r_sstatus() | SPP_USER);
    w_sie(r_sie() & ~(SIE_SSIE | SIE_STIE | SIE_SEIE));

    kstart();
}