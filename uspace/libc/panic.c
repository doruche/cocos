#include "libs/panic.h"
#include "libs/printf.h"
#include "uspace/syscall.h"
#include <stdarg.h>
#include "libs/types.h"
#include "uspace/task.h"

void __noreturn
__panic(const char* msg, ...) {
    va_list ap;
    va_start(ap, msg);
    printf("PANIC: ");
    vprintf(msg, ap);
    va_end(ap);
    exit();    
}