#include "kernel/syscall.h"
#include "kernel/misc/printk.h"
#include "libs/prelude.h"

SYSCALL_DEFINE2(
    dbg_puts, 
    const char*, str,
    usize, len
) {
    static char buf[256];
    if (len > array_size(buf) - 1) {
        panic("dbg_puts: len too large %ld", len);
    }
    trace("dbg_puts: str=%p, len=%ld", str, len); 
    memcpy(buf, str, len);
    buf[len] = '\0';
    printk("%s", buf);

    return 0;
}