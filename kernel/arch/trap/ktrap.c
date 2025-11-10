/*
 * kernel trap handling
 * we do not handle interrupts in kernel for simplicity
 */

#include "../arch.h"
#include <libs/prelude.h>
#include <kernel/arch/csr.h>
#include <kernel/arch/qemu-virt.h>
#include <kernel/task/sched.h>
#include <kernel/task/processor.h>
#include <kernel/misc/printk.h>

static const char* const
irq_str(u64 irq) {
    switch (irq) {
        case SCAUSE_IRQ_SOFT: return "Software Interrupt";
        case SCAUSE_IRQ_TIMER: return "Timer Interrupt";
        case SCAUSE_IRQ_EXT: return "External Interrupt";
        default: panic("Unknown IRQ %ld", irq);
    }

}

static const char* const exception_strs[] = {
    [SCAUSE_EXC_INST_MISALIGNED] = "Instruction address misaligned",
    [SCAUSE_EXC_INST_ACCESS] = "Instruction access fault",
    [SCAUSE_EXC_ILLEGAL_INST] = "Illegal instruction",
    [SCAUSE_EXC_BREAKPOINT] = "Breakpoint",
    [SCAUSE_EXC_LOAD_MISALIGNED] = "Load address misaligned",
    [SCAUSE_EXC_LOAD_ACCESS] = "Load access fault",
    [SCAUSE_EXC_STORE_MISALIGNED] = "Store/AMO address misaligned",
    [SCAUSE_EXC_STORE_ACCESS] = "Store/AMO access fault",
    [SCAUSE_EXC_ECALL_FROM_U] = "Environment call from U-mode",
    [SCAUSE_EXC_ECALL_FROM_S] = "Environment call from S-mode",
    [SCAUSE_EXC_INST_PAGE_FAULT] = "Instruction page fault",
    [SCAUSE_EXC_LOAD_PAGE_FAULT] = "Load page fault",
    [SCAUSE_EXC_STORE_PAGE_FAULT] = "Store page fault"
};

u64
ktrap(u64 prev_sp) {
    assert_eq(arch_intr_status(), false);

    if (scause_is_irq(r_scause())) {
        u64 irq = r_scause() & ~SCAUSE_IRQ_FLAG;
        if (irq == SCAUSE_IRQ_TIMER) {
            /* from arch/timer.c */
            extern void set_next_timer(void);
            set_next_timer();
        } else {
            /* should not reach here cz we disable external interrupts in kernel. */
            panic("ktrap: unhandled irq %ld (%s)",
                  irq, irq_str(irq));
        }
    } else {
        u64 exccode = r_scause();
        /* 
         * The invariable that
         * "if current_task == NULL then we are on scheduler context"
         * may be violated here. for example we may trap into here
         * during a context switch. but if we go here it must be a
         * serious error. we do not care about those cases for now,
         * just panic.
         */
        if (exccode < array_size(exception_strs) && exception_strs[exccode]) {
            if (current_task == NULL) {
                panic("Exception in scheduler: %s (sepc=0x%lx, stval=0x%lx)",
                      exception_strs[exccode], r_sepc(), r_stval());
            } else {
                panic("Exception in task: tid=%ld name=%s exccode=%s (sepc=0x%lx, stval=0x%lx)",
                      current_task->tid, current_task->name,
                      exception_strs[exccode], r_sepc(), r_stval());
            }
        } else {
            panic("Unknown Exception: %ld (sepc=0x%lx, stval=0x%lx)",
                  exccode, r_sepc(), r_stval());
        }
    }

    return prev_sp;
}