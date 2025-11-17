#include <libs/prelude.h>
#include <kernel/syscall.h>
#include <kernel/misc/printk.h>

SYSCALL_DEFINE2(
    dbg_puts, 
    const char*, str,
    usize, len
) {
    static char buf[256];
    if (len > array_size(buf) - 1) {
        panic("dbg_puts: len too large %ld", len);
    }
    pr_trace("dbg_puts: str=%p, len=%ld", str, len); 
    memcpy(buf, str, len);
    buf[len] = '\0';

    /* do not use printk to avoid confusion between kernel and user space */
    for (usize i = 0; i < len; i++) {
        arch_dbg_write(buf[i]);
    }
    
    return OK;
}