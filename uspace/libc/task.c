#include "libs/types.h"
#include "uspace/task.h"
#include "uspace/syscall.h"

void __noreturn
exit(void) {
    sys_kill(sys_gettid());
    __builtin_unreachable();
}