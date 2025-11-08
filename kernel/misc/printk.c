/*
 * print a kernel message.
 * we wrap printk to disable interrupts during printing
 * to avoid messy outputs.
 */

#include <libs/prelude.h>
#include <kernel/arch/arch.h>
#include <kernel/misc/printk.h>
#include <stdarg.h>

isize
vprintk(const char* fmt, va_list ap) {
    bool pre_intr_enabled = arch_intr_status();
    arch_intr_set(false);
    isize ret = vprintf(fmt, ap);
    if (pre_intr_enabled) {
        arch_intr_set(true);
    }
    return ret;
}

// we want this work.
// it should work everywhere.
isize
printk(const char* fmt, ...) {
    // do not use push/pop_intr_off here,
    // as printk will also be called in early booting stage,
    // when processor_init() is not called yet.
    
    bool pre_intr_enabled = arch_intr_status();
    arch_intr_set(false);
    va_list ap;
    va_start(ap, fmt);
    isize ret = vprintf(fmt, ap);
    va_end(ap);
    arch_intr_set(pre_intr_enabled);
    return ret;
}