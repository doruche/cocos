#include "libs/panic.h"
#include "libs/types.h"
#include "kernel/misc/printk.h"
#include "kernel/misc/log.h"

/* implement libgeneric's panic hook */

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