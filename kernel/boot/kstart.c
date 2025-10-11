#include "kernel/misc/printk.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "kernel/boot.h"
#include "kernel/arch/timer.h"
#include "kernel/arch/csr.h"
#include "kernel/mm/pm.h"
#include "kernel/mm/vm.h"
#include "kernel/misc/test.h"


void
kstart(bootinfo_t* bootinfo) {
    pm_init(bootinfo);
    info("pm initialized.");
    enable_intr();
    info("interrupt enabled.");
    timer_init();
    info("timer initialized.");
    kvms_init(bootinfo);    
    info("kernel vm space initialized.");
    
    slab_test();

    for (;;);

    unreachable()
}