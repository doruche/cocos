#pragma once
#include <libs/prelude.h>
#include <kernel/task/sched.h>

result_t    irq_listen(irq_t irqno, task_t* task);
result_t    irq_unlisten(irq_t irqno, task_t* task);
void        task_release_irq(task_t* task);
