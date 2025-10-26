#include "libs/printf.h"
#include "libs/prelude.h"
#include "uspace/syscall.h"
#include "libs/string.h"

usize
__puts(const char* str) {
    usize len = strlen(str);
    return sys_dbg_puts(str, len);
}