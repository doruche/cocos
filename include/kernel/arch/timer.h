/*
 * timer management
 */

#pragma once

#include "libs/prelude.h"

void    timer_init(void);
void    set_next_timer(void);
void    set_timer(usize cycles);
void    timer_intr(void);

static inline void
__wfi(void) {
    asm volatile("wfi");
}
