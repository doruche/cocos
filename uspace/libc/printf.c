#include <libs/hooks.h>
#include <libs/prelude.h>
#include <uspace/syscall.h>

usize __hook_impl
__puts(const char* str) {
    usize len = strlen(str);
    return sys_dbg_puts(str, len);
}