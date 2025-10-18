#include "kernel/task/processor.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "libs/macros.h"
#include "libs/types.h"
#include "kernel/syscall.h"

SYSCALL_DEFINE1(kill, tid_t, tid) {
    task_t* task = task_get(tid);
    if (task == NULL) {
        return -1;
    }
    tid_t current_tid = current_task->tid;
    if (task->tid == current_tid) {
        task_crash_exit();
    } else {
        task_kill(tid);
    }
    return 0;
}

SYSCALL_DEFINE0(gettid) {
    return current_task->tid;
}