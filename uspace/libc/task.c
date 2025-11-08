#include <libs/prelude.h>
#include <uspace/task.h>
#include <uspace/syscall.h>

void __noreturn
task_exit(result_t exit_code) {
    sys_task_exit(exit_code);
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