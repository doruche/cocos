#include "kernel/arch/sbi.h"
#include "kernel/misc/printk.h"

void
kstart(void) {
#include "kernel/misc/test.h"
    printk_test();
    // panic_test();

    sbi_shutdown();
}