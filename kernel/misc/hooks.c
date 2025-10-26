/*
 * libgeneric's hooks
 */

#include "libs/panic.h"
#include "libs/printf.h"
#include "libs/prelude.h"
#include "kernel/misc/printk.h"
#include "libs/log.h"
#include "kernel/arch/sbi.h"

usize
__puts(const char* str) {
    usize len = 0;
    while (str[len] != '\0') {
        sbi_console_putchar(str[len]);
        len++;
    }
    return len;
}

void __noreturn
__panic(const char* msg, ...) {
    va_list ap;
    va_start(ap, msg);
    printk(COLOR_PANIC "[PANIC|%s:%d]\t", __FILE__, __LINE__);
    vprintk(msg, ap);
    printk("\n" COLOR_RESET);
    va_end(ap);
    sbi_shutdown();
    __builtin_unreachable();
}

void __noreturn
__panic_no_msg(void) {
    sbi_shutdown();
    __builtin_unreachable();
}