#include "libs/prelude.h"
#include "uspace/task.h"
#include "uspace/syscall.h"

void __noreturn
task_exit(void) {
    sys_task_kill(sys_task_gettid());
    __builtin_unreachable();
}

void
task_yield(void) {
    sys_task_yield();
}

tid_t
task_gettid(void) {
    static tid_t cached = 0;
    if (cached == 0) {
        cached = (tid_t)sys_task_gettid();
    }
    return cached;
}