#include "kernel/misc/printk.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "kernel/boot.h"
#include "kernel/arch/timer.h"
#include "kernel/arch/csr.h"
#include "kernel/mm/pm.h"
#include "kernel/misc/test.h"

void
kstart(bootinfo_t* bootinfo) {
    palloc_init(bootinfo);
    info("palloc initialized.");

    enable_intr();
    timer_init();

    pm_test();

    for(;;);

    unreachable()
}