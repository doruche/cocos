/*
 * timer management 
 */

#include "arch.h"
#include <libs/prelude.h>
#include <kernel/arch/csr.h>
#include <kernel/arch/sbi.h>
#include <kernel/arch/qemu-virt.h>

static const u64 INTERVAL = FREQUENCY / 10;

void
set_next_timer(void) {
    arch_timer_set(rdtime() + INTERVAL);
}

u64
arch_timer_get(void) {
    return rdtime();
}

void
arch_timer_init(void) {
    w_sie(r_sie() | SIE_STIE);
    set_next_timer();
}
