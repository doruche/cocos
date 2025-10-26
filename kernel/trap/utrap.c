/*
 * uspace trap handling
 */

#include "kernel/mm/vm.h"
#include "kernel/task/sched.h"
#include "kernel/trap.h"
#include "libs/log.h"
#include "libs/assert.h"
#include "kernel/arch/csr.h"
#include "libs/prelude.h"

#include "kernel/arch/ctx.h"
#include "kernel/task/processor.h"
#include "kernel/syscall.h"
#include "kernel/arch/ctx.h"
#include "kernel/arch/timer.h"

__maybe_unused
static const char* const
irq_str(u64 irq) {
    switch (irq) {
        case SCAUSE_IRQ_SOFT: return "Software Interrupt";
        case SCAUSE_IRQ_TIMER: return "Timer Interrupt";
        case SCAUSE_IRQ_EXT: return "External Interrupt";
        default: panic("Unknown IRQ %ld", irq);
    }

}

__maybe_unused
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

void
utrap() {
    trace("user trap!");

    // sanity check
    task_t* current = unwrap_null(current_task);
    trapframe_t* tf = &current->actx->tf;
    assert_eq(current->state, T_RUNNING);
    assert(!intr_enabled());

    actx_utrap_entry(current->actx);

    if (scause_is_irq(r_scause())) {
        u64 irq = r_scause() & ~SCAUSE_IRQ_FLAG;
        switch (irq) {
            case SCAUSE_IRQ_TIMER: {
                    // trace("user timer interrupt");
                    // timer_intr(); // avoid double handling timer intr
                    // ugly logic, refine later
                    yield();
                }
                break;
            default:
                panic("Unhandled user IRQ: %s", irq_str(irq));
        }
    } else {
        u64 exccode = r_scause();
        switch (exccode) {
            case SCAUSE_EXC_ECALL_FROM_U: {
                    // syscall
                    if (!do_syscall(
                        tf->x[17], // a7
                        tf
                    )) {
                        // invalid syscall, kill the task
                        warn("invalid syscall %ld from task %d",
                            tf->x[17],
                            current->tid
                        );
                        task_crash_exit();
                    }
                }
                break;
            case SCAUSE_EXC_INST_PAGE_FAULT:
            case SCAUSE_EXC_LOAD_PAGE_FAULT:
            case SCAUSE_EXC_STORE_PAGE_FAULT: {
                    uaddr_t fault_addr = r_stval();
                    // currently just kill the task on page fault
                    task_t* current = unwrap_null(current_task);
                    notify(
                        "task page fault: tid=%ld name=%s addr=0x%lx pc=0x%lx exccode=%s",
                        current->tid, current->name,
                        fault_addr, r_sepc(), exception_strs[exccode]
                    );
                    if (task_get(current->pager) != NULL) {
                        notify(
                            "task page fault: requesting pager task %ld to handle",
                            current->pager
                        );
                        yield();
                    } else {
                        warn(
                            "task page fault: no valid pager for task %ld, killing",
                            current->tid
                        );
                        task_crash_exit();
                    }
                }
                break;
            default:
                panic("Unhandled user exception: %s (sepc=0x%lx, stval=0x%lx)",
                      (exccode < array_size(exception_strs) && exception_strs[exccode]) ?
                        exception_strs[exccode] : "Unknown",
                      r_sepc(), r_stval());
        }
    }

    utrap_ret();
}

// such a weird split is useful when creating a new task,
// whose ctx.ra is set to here.
__noreturn
void
utrap_ret() {
    task_t* current = unwrap_null(current_task);
    assert_eq(current->state, T_RUNNING);

    trace("returning to user space task tid=%ld name=%s",
        current->tid, current->name);

    actx_utrap_ret(current->actx);

    trace("jumping to user space...");

    flush(); // flush console output buffer before returning to user space

    vaddr_t hook = TRAMPOLINE + 
        ((u64)u_trampoline_ret - (u64)u_trampoline_entry);
    ((void (*)(void))hook)();

    unreachable();
}