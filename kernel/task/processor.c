#include "kernel/task/processor.h"
#include "kernel/arch/ctx.h"
#include "kernel/task/sched.h"
#include "kernel/misc/assert.h"
#include "kernel/mm/vm.h"
#include "kernel/mm/pm.h"
#include "libs/types.h"
#include "kernel/consts/params.h"
#include "kernel/arch/timer.h"

processor_t processor;

void
processor_init(void) {
    processor.cur_task = NULL;
    kaddr_t sched_kstack_top = task_kstack_top(-1);
    ctx_init(
        &processor.sched_ctx,
        (kaddr_t)sched,
        sched_kstack_top
    );

    // alright! finally, let's map TRAMPOLINE and scheduler kstack
    extern vm_space_t kernel_vms;
    vm_map(
        &kernel_vms,
        (vpn_t)PA2PN(TRAMPOLINE),
        (ppn_t)PA2PN(TRAMPOLINE),
        1,
        VM_RESERVED, // trampoline should never be freed
        VM_EXEC | VM_READ
    );
    ppn_t kstack_ppn = unwrap_err(palloc(KSTACK_SIZE / PAGE_SIZE));
    vm_map(
        &kernel_vms,
        (vpn_t)((sched_kstack_top - KSTACK_SIZE) / PAGE_SIZE),
        kstack_ppn,
        KSTACK_SIZE / PAGE_SIZE,
        VM_ALLOCATED,
        VM_READ | VM_WRITE | VM_CONTIGUOUS
    );
    vm_map(
        &kernel_vms,
        (vpn_t)((sched_kstack_top - KSTACK_SIZE) / PAGE_SIZE - 1),
        VM_FAKE_PPN,
        1,
        VM_RESERVED,
        VM_FAKE | VM_READ | VM_WRITE
    );
    // and then jump to scheduler context...
}

void
wait_for_intr(void) {
    __wfi();
}