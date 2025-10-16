/*
 * uspace trap handling
 */

#include "kernel/mm/vm.h"
#include "kernel/task/sched.h"
#include "kernel/trap.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "kernel/arch/csr.h"

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
    todo()
    utrap_ret();
}

// such a weird split is useful when creating a new process,
// whose ctx.ra is set to here.
__maybe_unused
__noreturn
void
utrap_ret() {
    todo()
}