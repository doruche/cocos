#include <libs/prelude.h>
#include <kernel/task/sched.h>
#include <kernel/task/processor.h>

/*
 * Unfortunately, or to say, practically, we do not support interrupt handling from kernel.
 * If we do that, a lot of codes should be modified or added
 * to keep the invariables of all kinds of kernel resources,
 * such as current_task (processor's field), address spaces, ports, etc,
 * which is too complex for this teaching kernel.
 * So only interrupts from user space will be considered.
 * By the way, the above does not mean we should disable interrupts in kernel.
 * If we do not access any of the above resources in kernel,
 * interrupts can be enabled safely.
 * 
 * Must mention that, we can ignore timer interrupts in kernel and do not yield
 * for simplicity, as is a conservative approach, which does not affect correctness.
 * However, external interrupts should be handled properly even in kernel,
 * otherwise devices may not work as expected. To deal this tricky situation,
 * we just disable external interrupts in kernel, and defer their handling to user space.
 *
 * All the above trade-offs and strategies have already been done in HAL layer. 
 * Following two handlers are all user trap handlers.
 * You can assume safely that the invariables mentioned above always hold
 * when entering these handlers.
 */

void
timer_intr(void) {
    trace("timer_intr: user timer interrupt");
    task_yield();
}

void
dev_intr(irq_t irqno) {
    warn("dev_intr: external interrupt: irq %d", irqno);
    warn("dev_intr: currently not implemented");
}


