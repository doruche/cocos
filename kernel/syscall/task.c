#include <kernel/task/processor.h>
#include <kernel/ipc.h>
#include <libs/prelude.h>
#include <kernel/syscall.h>
#include <kernel/task/sched.h>

SYSCALL_DEFINE1(task_kill, tid_t, tid) {
    trace("sys_task_kill: called for tid=%ld", tid);

    if (tid == current_task->tid) {
        trace("sys_task_kill: task cannot kill itself");
        return -ERR_INVAL;
    } 

    result_t ret = task_kill(tid);
    if (is_err(ret)) {
        trace("sys_task_kill: failed to kill task tid=%ld: %s",
            tid, strerr(ret));
        return ret;
    }
    trace("sys_task_kill: successfully killed task tid=%ld", tid);
    return OK;
}

SYSCALL_DEFINE0(task_gettid) {
    trace("sys_task_gettid: called");
    return (unwrap_null(current_task))->tid;
}

SYSCALL_DEFINE3(task_spawn, const char*, name, uaddr_t, entry, asid_t, asid) {
    task_t* task = NULL;
    result_t ret = task_spawn(name, entry, asid, &task);
    if (is_err(ret)) {
        warn("sys_task_spawn: failed to spawn task %s: %s",
            name, strerr(ret));
        return ret;
    }
    trace("sys_task_spawn: successfully spawned task %s with tid=%ld",
        name, task->tid);
    return task->tid;
}

SYSCALL_DEFINE0(task_yield) {
    task_t* current = unwrap_null(current_task);
    trace("sys_task_yield: called by task tid=%ld name=%s",
        current->tid, current->name);
    task_yield();
    return OK;
}

SYSCALL_DEFINE1(task_block, tid_t, tid) {
    task_t* current = unwrap_null(current_task);
    trace("sys_task_block: called by task tid=%ld name=%s to block tid=%ld",
        current->tid, current->name, tid);
    if (tid == current->tid) {
        trace("sys_task_block: task cannot block itself");
        return -ERR_INVAL;
    }

    result_t ret = task_block(tid);
    if (is_err(ret)) {
        warn("sys_task_block: failed to block task tid=%ld: %s",
            tid, strerr(ret));
        return ret;
    }
    trace("sys_task_block: successfully blocked task tid=%ld", tid);
    return OK;
}

SYSCALL_DEFINE1(task_resume, tid_t, tid) {
    task_t* current = unwrap_null(current_task);
    trace("sys_task_resume: called by task tid=%ld name=%s to resume tid=%ld",
        current->tid, current->name, tid);
    if (tid == current->tid) {
        trace("sys_task_resume: task cannot resume itself");
        return -ERR_INVAL;
    }
    result_t ret = task_resume(tid);
    if (is_err(ret)) {
        warn("sys_task_resume: failed to resume task tid=%ld: %s",
            tid, strerr(ret));
        return ret;
    }
    trace("sys_task_resume: successfully resumed task tid=%ld", tid);
    return OK;
}

SYSCALL_DEFINE1(task_exit, result_t, exit_code) {
    task_t* current = unwrap_null(current_task);
    trace("sys_task_exit: called by task tid=%ld name=%s with exit code %ld",
        current->tid, current->name, exit_code);
    task_crash_exit(exit_code);
    unreachable();   
}
