#include "kernel/task/processor.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "libs/macros.h"
#include "libs/types.h"
#include "kernel/syscall.h"
#include "kernel/task/sched.h"

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

SYSCALL_DEFINE3(spawn, const char*, name, uaddr_t, entry, tid_t, pager) {
    trace("sys_spawn: called name=%s entry=0x%lx pager=%ld",
        name, entry, pager);

    task_t* pager_task = task_get(pager);
    if (pager_task == NULL) {
        trace("sys_spawn: invalid pager tid=%ld", pager);
        return -1;
    }

    task_t* task = task_spawn(name, entry, pager_task);
    trace("sys_spawn: spawned task tid=%ld name=%s entry=0x%lx pager=%ld",
        task->tid, task->name, entry, pager);

    return task->tid;
}