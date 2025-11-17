/*
 * uspace trap handling
 */

#include "../arch.h"
#include <libs/prelude.h>
#include <kernel/arch/csr.h>
#include <kernel/arch/trap.h>
#include <kernel/arch/qemu-virt.h>
#include <kernel/task/sched.h>
#include <kernel/task/processor.h>
#include <kernel/misc/printk.h>
#include <kernel/syscall.h>

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

static void
prepare_utrap_entry(void) {
    task_t* current = unwrap_null(current_task);
    assert_eq(current->state, T_RUNNING);
    // gprs & sscratch already stored by asm code
    arch_ctx_t* ctx = current->actx;
    ctx->tf.sepc = r_sepc();
    ctx->tf.sstatus = r_sstatus();
    // change to kernel trap handler
    w_stvec(STVEC((u64)ktrap_trampoline, STVEC_MODE_DIRECT));
    // disable external interrupts in kernel
    w_sie(r_sie() & ~SIE_SEIE);
    enable_intr();
}

static void
prepare_utrap_ret(void) {
    task_t* current = unwrap_null(current_task);
    assert_eq(current->state, T_RUNNING);
    arch_ctx_t* ctx = current->actx;

    assert(arch_intr_status() == true);
    arch_intr_set(false);
    w_sepc(ctx->tf.sepc);
    w_sstatus(ctx->tf.sstatus);
    w_sscratch((u64)ctx);
    // change to user trap handler
    w_stvec(STVEC((u64)u_trampoline_entry, STVEC_MODE_DIRECT));
    // enable external interrupts in user space
    w_sie(r_sie() | SIE_SEIE);
}

void
utrap() {
    printk("\n");
    pr_trace("user trap!");

    prepare_utrap_entry();

    if (scause_is_irq(r_scause())) {
        irq_t irqno = r_scause() & ~SCAUSE_IRQ_FLAG;
        switch (irqno) {
            case SCAUSE_IRQ_TIMER: 
                extern void timer_intr(void);
                timer_intr();
                break;
            case SCAUSE_IRQ_EXT: 
                pr_trace("utrap: external interrupt");
                // todo: plic
                extern void dev_intr(irq_t irqno);
                dev_intr(irqno);
                break;
            case SCAUSE_IRQ_SOFT:
                unreachable();
            default:
                unreachable();
        }
    } else {
        u64 exccode = r_scause();
        task_t* current = unwrap_null(current_task);
        switch (exccode) {
            case SCAUSE_EXC_ECALL_FROM_U:
                // syscall
                arch_trapframe_t* tf = &current->actx->tf;
                if (is_err(syscall_dispatch(
                    tf->x[17], 
                    tf
                ))) {
                    // invalid syscall, kill the task
                    pr_warn("invalid syscall %ld from task %d",
                        tf->x[17],
                        current->tid   
                    );
                    // task_crash_exit(-ERR_INVALID_SYSCALL);
                    task_exit(-ERR_INVALID_SYSCALL);
                }
                // not cover all cases.
                // actually if a syscall has changed sepc,
                // we should not just add 4 here.
                // but for now there is no such syscall.
                tf->sepc += 4;
                break;
            case SCAUSE_EXC_INST_PAGE_FAULT:
            case SCAUSE_EXC_LOAD_PAGE_FAULT:
            case SCAUSE_EXC_STORE_PAGE_FAULT: 
                uaddr_t fault_addr = r_stval();
                // currently just kill the task on page fault
                pr_notify(
                    "task page fault: tid=%ld name=%s addr=0x%lx pc=0x%lx exccode=%s",
                    current->tid, current->name,
                    fault_addr, r_sepc(), exception_strs[exccode]
                );
                task_exit(-ERR_PAGEFAULT);
                break;
            default:
                panic("Unhandled user exception: %s (sepc=0x%lx, stval=0x%lx)",
                      (exccode < array_size(exception_strs) && exception_strs[exccode]) ?
                        exception_strs[exccode] : "Unknown",
                      r_sepc(), r_stval());
        }
    }

    arch_utrap_ret();
}

// such a weird split is useful when creating a new task,
// whose ctx.ra is set to here.
__noreturn
void
arch_utrap_ret() {
    task_t* current = unwrap_null(current_task);
    pr_trace("returning to user space task tid=%ld name=%s",
        current->tid, current->name);

    prepare_utrap_ret();

    printf_flush(); // flush console output buffer before returning to user space

    vaddr_t hook = TRAMPOLINE + 
        ((u64)u_trampoline_ret - (u64)u_trampoline_entry);
    ((void (*)(void))hook)();

    unreachable();
}