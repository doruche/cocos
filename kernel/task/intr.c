#include <libs/prelude.h>
#include <kernel/arch/arch.h>
#include <kernel/task/sched.h>
#include <kernel/task/processor.h>
#include <kernel/ipc.h>

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

static task_t* irq_owners[IRQ_MAX];

void
timer_intr(void) {
    pr_trace("timer_intr: user timer interrupt");
    task_yield();
}


void
dev_intr(irq_t irqno) {
    pr_notify("dev_intr: external interrupt: irq %d", irqno);
    task_t* owner = irq_owners[irqno];

    /*
     * if this interrupt happens, then it must be listened by some task.
     * otherwise, it is a serious error.
     */
    assert(owner != NULL);
    unwrap_err(notify(owner, NOTIF_IRQ));

    /* temperarily disable it, let driver acknowledge it */
    arch_irq_disable(irqno);
}

result_t
irq_listen(irq_t irqno, task_t* task) {
    if (irqno >= IRQ_MAX) {
        pr_warn("irq_listen: invalid irqno %d", irqno);
        return -ERR_INVAL;
    }
    if (irq_owners[irqno] != NULL) {
        pr_warn("irq_listen: irqno %d already owned by task tid=%ld name=%s",
            irqno,
            irq_owners[irqno]->tid,
            irq_owners[irqno]->name
        );
        return -ERR_DEV_BUSY;
    }
    irq_owners[irqno] = task;
    arch_irq_enable(irqno);
    pr_notify("irq_listen: task tid=%ld name=%s listening on irq %d",
        task->tid, task->name, irqno);
    return OK;
}

result_t
irq_unlisten(irq_t irqno, task_t* task) {
    if (irqno >= IRQ_MAX) {
        pr_warn("irq_unlisten: invalid irqno %d", irqno);
        return -ERR_INVAL;
    }
    if (irq_owners[irqno] != task) {
        pr_warn("irq_unlisten: irqno %d not owned by task tid=%ld name=%s",
            irqno,
            task->tid,
            task->name
        );
        return -ERR_PERM;
    }
    irq_owners[irqno] = NULL;
    arch_irq_disable(irqno);
    pr_notify("irq_unlisten: task tid=%ld name=%s unlistening on irq %d",
        task->tid, task->name, irqno);
    return OK;
}

void
task_release_irq(task_t* task) {
    for (irq_t irqno = 0; irqno < IRQ_MAX; irqno++) {
        if (irq_owners[irqno] == task) {
            unwrap_err(irq_unlisten(irqno, task));
        }
    }
}
