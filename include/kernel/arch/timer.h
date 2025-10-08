/*
 * timer management
 */

#ifndef KERNEL_ARCH_TIMER_H
#define KERNEL_ARCH_TIMER_H 1

#define INTERVAL 10000000

void    timer_init(void);
void    set_next_timer(void);
void    timer_intr(void);

#endif