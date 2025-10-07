/*
 * timer management 
 */

#include "kernel/arch/timer.h"
#include "kernel/arch/sbi.h"
#include "kernel/arch/csr.h"
#include "kernel/misc/log.h"

void
set_next_timer(void) {
    sbi_set_timer(rdtime() + INTERVAL);
}

void
timer_init(void) {
    w_sie(r_sie() | SIE_STIE);
    set_next_timer();
}

void
timer_intr(void) {
    trace("timer interrupt!");
    set_next_timer();
}