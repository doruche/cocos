#include "kernel/task/processor.h"
#include "kernel/ipc.h"
#include "libs/prelude.h"
#include "kernel/syscall.h"
#include "kernel/task/sched.h"

SYSCALL_DEFINE1(task_kill, tid_t, tid) {
    trace("sys_task_kill: called for tid=%ld", tid);

    task_t* task = task_get(tid);
    if (task == NULL) {
        return -ERR_NOENT;
    }
    tid_t current_tid = (unwrap_null(current_task))->tid;
    if (tid == current_tid) {
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

SYSCALL_DEFINE0(task_gettid) {
    trace("sys_task_gettid: called");
    return (unwrap_null(current_task))->tid;
}

SYSCALL_DEFINE3(task_spawn, const char*, name, uaddr_t, entry, port_t, pager) {
    trace("sys_task_spawn: called name=%s entry=0x%lx pager=%ld",
        name, entry, pager);

    // todo: validate pager port

    task_t* task = task_spawn(name, entry, pager);
    trace("sys_task_spawn: spawned task tid=%ld name=%s entry=0x%lx pager=%ld",
        task->tid, task->name, entry, pager);

    return task->tid;
}

SYSCALL_DEFINE0(task_yield) {
    task_t* current = unwrap_null(current_task);
    trace("sys_task_yield: called by task tid=%ld name=%s",
        current->tid, current->name);
    task_yield();
    return 0;
}

SYSCALL_DEFINE1(task_block, tid_t, tid) {
    task_t* current = unwrap_null(current_task);
    trace("sys_task_block: called by task tid=%ld name=%s to block tid=%ld",
        current->tid, current->name, tid);
    if (tid == current->tid) {
        trace("sys_task_block: task cannot block itself");
        return -ERR_INVAL;
    }

    if (task_get(tid) == NULL) {
        trace("sys_task_block: no such task tid=%ld", tid);
        return -ERR_NOENT;
    }
    task_block(tid);
    return 0;
}

SYSCALL_DEFINE1(task_resume, tid_t, tid) {
    task_t* current = unwrap_null(current_task);
    trace("sys_task_resume: called by task tid=%ld name=%s to resume tid=%ld",
        current->tid, current->name, tid);
    if (tid == current->tid) {
        trace("sys_task_resume: task cannot resume itself");
        return -ERR_INVAL;
    }
    if (task_get(tid) == NULL) {
        trace("sys_task_resume: no such task tid=%ld", tid);
        return -ERR_NOENT;
    }
    task_resume(tid);
    return 0;
}