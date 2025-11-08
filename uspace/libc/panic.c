#include "libs/hooks.h"
#include "uspace/syscall.h"
#include <stdarg.h>
#include "libs/prelude.h"
#include "uspace/task.h"

void __noreturn __hook_impl
__panic(const char* msg, ...) {
    va_list ap;
    va_start(ap, msg);
    printf("PANIC: ");
    vprintf(msg, ap);
    va_end(ap);
    task_exit(-ERR_PANIC);
}

void __noreturn __hook_impl
__panic_no_msg(void) {
    task_exit(-ERR_PANIC);
}