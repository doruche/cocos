#include "libs/printf.h"
#include "libs/types.h"
#include "uspace/syscall.h"

usize
__puts(const char* str) {
    sys_dbg_puts(str);
    usize len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}