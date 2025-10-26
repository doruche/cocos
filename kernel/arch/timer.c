/*
 * timer management 
 */

#include "kernel/arch/timer.h"
#include "kernel/consts/params.h"
#include "kernel/arch/sbi.h"
#include "kernel/arch/csr.h"
#include "libs/log.h"

void
set_next_timer(void) {
    sbi_set_timer(rdtime() + INTERVAL);
}

void
set_timer(usize cycles) {
    sbi_set_timer(rdtime() + cycles * INTERVAL);
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
    // todo: detect double claim
    trace("timer interrupt!");
    set_next_timer();
}