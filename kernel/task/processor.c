#include "kernel/task/processor.h"
#include "kernel/arch/ctx.h"
#include "kernel/task/sched.h"
#include "libs/assert.h"
#include "kernel/mm/vm.h"
#include "kernel/mm/pm.h"
#include "libs/types.h"
#include "kernel/consts/params.h"
#include "kernel/arch/timer.h"
#include "kernel/trap.h"
#include "kernel/arch/csr.h"

processor_t processor;

void
processor_init(void) {
    processor.cur_task = NULL;
    kaddr_t sched_kstack_top = task_kstack_top(-1);
    ctx_init(
        &processor.sched_ctx,
        (kaddr_t)scheduler,
        sched_kstack_top
    );

    // alright! finally we're to map TRAMPOLINE and scheduler kstack
    extern vm_space_t kernel_vms;
    vm_map(
        &kernel_vms,
        (vpn_t)PA2PN(TRAMPOLINE),
        (ppn_t)PA2PN((kaddr_t)u_trampoline_entry),
        1,
        VM_READ | VM_EXEC
    );
    unwrap_err(vm_alloc(
        &kernel_vms,
        (vpn_t)((sched_kstack_top - KSTACK_SIZE) / PAGE_SIZE),
        KSTACK_SIZE / PAGE_SIZE,
        VM_READ | VM_WRITE
    ));
    vm_map(
        &kernel_vms,
        (vpn_t)((sched_kstack_top - KSTACK_SIZE) / PAGE_SIZE - 1),
        0,
        1,
        VM_READ | VM_WRITE | VM_FAKE
    );
    // and then jump to scheduler context...
}

void
wait_for_intr(void) {
    __wfi();
}

void
push_intr_off(void) {
    if (processor.intr_off_count == 0) {
        processor.prev_intr_state = intr_enabled();
        disable_intr();
    }
    assert(!intr_enabled());
    processor.intr_off_count++;
}

void
pop_intr_off(void) {
    assert(processor.intr_off_count > 0);
    processor.intr_off_count--;
    if (processor.intr_off_count == 0 && processor.prev_intr_state) {
        enable_intr();
    }
}