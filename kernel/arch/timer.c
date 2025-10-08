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

/*
 * Enable timer interrupt and set the first timer interrupt event.
 */
void
timer_init(void) {
    w_sie(r_sie() | SIE_STIE);
    set_next_timer();
}

/*
 * Timer interrupt handler.
 */

void
timer_intr(void) {
    // trace("timer interrupt!");
    set_next_timer();
}