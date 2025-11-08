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
    info("physical page allocator initialized.");
    arch_kvm_init();
    info("kernel virtual memory initialized.");
    kmalloc_init();
    info("kernel heap allocator initialized.");
    as_init();
    info("address space subsystem initialized.");
    ipc_init();
    info("ipc subsystem initialized.");
    arch_timer_init();
    info("timer initialized.");
    arch_intr_set(true);
    info("interrupts enabled.");
 
    // vm_test();

    notify("cocos kernel booted successfully, jumping to scheduler...");
    sched_init(bootinfo->bootimage);

    unreachable()
}