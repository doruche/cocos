#include <libs/hooks.h>
#include <libs/prelude.h>
#include <uspace/syscall.h>

usize __hook_impl
__puts(const char* str) {
    /*
     * use strlen() here may cause an
     * linking error. idk why, maybe some
     * dependency issue? refine later.
     */
    usize len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return sys_dbg_puts(str, len);
}