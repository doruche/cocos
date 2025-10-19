#include "kernel/task/processor.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "libs/macros.h"
#include "libs/types.h"
#include "kernel/syscall.h"

SYSCALL_DEFINE1(kill, tid_t, tid) {
    trace("sys_kill: called for tid=%ld", tid);

    task_t* task = task_get(tid);
    if (task == NULL) {
        return -1;
    }
    tid_t current_tid = (unwrap_null(current_task))->tid;
    if (task->tid == current_tid) {
        trace("sys_kill: task killing itself tid=%ld name=%s",
            task->tid, task->name);
        task_crash_exit();
    } else {
        trace("sys_kill: killing task tid=%ld name=%s",
            task->tid, task->name);
        task_kill(tid);
    }
    return 0;
}

SYSCALL_DEFINE0(gettid) {
    return (unwrap_null(current_task))->tid;
}