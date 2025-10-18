#include "kernel/syscall.h"
#include "kernel/misc/printk.h"
#include "kernel/misc/log.h"

SYSCALL_DEFINE1(puts, const char*, str) {
    trace("sys_puts: %p", str);
    printk("%s", str);
    return 0;
}