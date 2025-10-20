#include "libs/printf.h"
#include "libs/types.h"
#include "uspace/syscall.h"

usize
__putc(char c) {
    static char buf[2];
    buf[0] = c;
    buf[1] = '\0';
    sys_puts(buf);
    return 1;
}