#include <kernel/arch/arch.h>
#include <kernel/misc/test.h>
#include <kernel/mm/pm.h>
#include <kernel/mm/as.h>
#include <kernel/mm/kmalloc.h>
#include <kernel/ipc.h>
#include <kernel/task/sched.h>


void __noreturn
kstart(bootinfo_t* bootinfo) {
    pm_init(bootinfo);
    pr_info("physical page allocator initialized.");
    arch_kvm_init();
    pr_info("kernel virtual memory initialized.");
    arch_ctx_mm_init();
    pr_info("architecture-specific context subsystem initialized.");
    kmalloc_init();
    pr_info("kernel heap allocator initialized.");
    as_init();
    pr_info("ipc subsystem initialized.");
    arch_timer_init();
    pr_info("timer initialized.");
    arch_intr_set(true);
    pr_info("interrupts enabled.");
 
    // vm_test();

    pr_notify("cocos kernel booted successfully, jumping to scheduler...");
    sched_init(bootinfo->bootimage);

    unreachable()
}