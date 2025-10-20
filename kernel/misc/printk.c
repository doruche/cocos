/*
 * print a kernel message.
 * this implementation supports:
 * 1. %[l]<b|o|d|x>
 * 2. %p
 * 3. %c, %s
 * 4. %%
 * format specifiers.
 */

#include "kernel/misc/printk.h"
#include "kernel/arch/sbi.h"
#include "kernel/misc/log.h"
#include "libs/types.h"
#include "kernel/arch/csr.h"
#include "libs/printf.h"
#include <stdarg.h>

usize
__putc(char c) {
    sbi_console_putchar(c);
    return 1;
}

isize
vprintk(const char* fmt, va_list ap) {
    bool pre_intr_enabled = intr_enabled();
    disable_intr();
    isize ret = vprintf(fmt, ap);
    if (pre_intr_enabled) {
        enable_intr();
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
    
    bool pre_intr_enabled = intr_enabled();
    disable_intr();
    va_list ap;
    va_start(ap, fmt);
    isize ret = vprintf(fmt, ap);
    va_end(ap);
    if (pre_intr_enabled) {
        enable_intr();
    }
    return ret;
}