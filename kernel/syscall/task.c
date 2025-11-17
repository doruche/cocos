#include <kernel/task/processor.h>
#include <kernel/ipc.h>
#include <libs/prelude.h>
#include <kernel/syscall.h>
#include <kernel/task/sched.h>
#include <kernel/task/irq.h>

SYSCALL_DEFINE1(task_destroy, tid_t, tid) {
    pr_trace("sys_task_destroy: called for tid=%ld", tid);

    if (tid == current_task->tid) {
        pr_trace("sys_task_destroy: task cannot destroy itself");
        return -ERR_INVAL;
    } 

    result_t ret = task_destroy(tid);
    if (is_err(ret)) {
        pr_trace("sys_task_destroy: failed to destroy task tid=%ld: %s",
            tid, strerr(ret));
        return ret;
    }
    pr_trace("sys_task_destroy: successfully destroyed task tid=%ld", tid);
    return OK;
}

SYSCALL_DEFINE0(task_gettid) {
    pr_trace("sys_task_gettid: called");
    return (unwrap_null(current_task))->tid;
}

SYSCALL_DEFINE3(task_spawn, const char*, name, uaddr_t, entry, asid_t, asid) {
    task_t* task = NULL;
    result_t ret = task_spawn(name, entry, asid, &task);
    if (is_err(ret)) {
        pr_warn("sys_task_spawn: failed to spawn task %s: %s",
            name, strerr(ret));
        return ret;
    }
    pr_trace("sys_task_spawn: successfully spawned task %s with tid=%ld",
        name, task->tid);
    return task->tid;
}

SYSCALL_DEFINE0(task_yield) {
    task_t* current = unwrap_null(current_task);
    pr_trace("sys_task_yield: called by task tid=%ld name=%s",
        current->tid, current->name);
    task_yield();
    return OK;
}

SYSCALL_DEFINE1(task_block, tid_t, tid) {
    task_t* current = unwrap_null(current_task);
    pr_trace("sys_task_block: called by task tid=%ld name=%s to block tid=%ld",
        current->tid, current->name, tid);
    if (tid == current->tid) {
        pr_trace("sys_task_block: task cannot block itself");
        return -ERR_INVAL;
    }

    result_t ret = task_block(tid);
    if (is_err(ret)) {
        pr_warn("sys_task_block: failed to block task tid=%ld: %s",
            tid, strerr(ret));
        return ret;
    }
    pr_trace("sys_task_block: successfully blocked task tid=%ld", tid);
    return OK;
}

SYSCALL_DEFINE1(task_resume, tid_t, tid) {
    task_t* current = unwrap_null(current_task);
    pr_trace("sys_task_resume: called by task tid=%ld name=%s to resume tid=%ld",
        current->tid, current->name, tid);
    if (tid == current->tid) {
        pr_trace("sys_task_resume: task cannot resume itself");
        return -ERR_INVAL;
    }
    result_t ret = task_resume(tid);
    if (is_err(ret)) {
        pr_warn("sys_task_resume: failed to resume task tid=%ld: %s",
            tid, strerr(ret));
        return ret;
    }
    pr_trace("sys_task_resume: successfully resumed task tid=%ld", tid);
    return OK;
}

SYSCALL_DEFINE1(task_exit, result_t, exit_code) {
    task_t* current = unwrap_null(current_task);
    pr_trace("sys_task_exit: called by task tid=%ld name=%s with exit code %ld",
        current->tid, current->name, exit_code);
    task_exit(exit_code);
    unreachable();   
}
SYSCALL_DEFINE1(task_getzombie, zombie_task_t*, out) {
    pr_trace("sys_task_getzombie: called");
    zombie_task_t zombie;
    result_t ret = task_getzombie(&zombie);
    if (is_err(ret)) {
        pr_warn("sys_task_getzombie: no zombie tasks available: %s",
            strerr(ret));
        return ret;
    }
    memcpy(out, &zombie, sizeof(zombie_task_t));
    pr_trace("sys_task_getzombie: got zombie task tid=%ld with exit code %ld",
        zombie.tid, zombie.exit_code);
    return OK;
}

SYSCALL_DEFINE1(irq_listen, irq_t, irqno) {
    task_t* current = unwrap_null(current_task);
    pr_trace("sys_irq_listen: called by task tid=%ld name=%s to listen irq %d",
        current->tid, current->name, irqno);
    result_t ret = irq_listen(irqno, current);
    if (is_err(ret)) {
        pr_warn("sys_irq_listen: failed to listen irq %d by task tid=%ld name=%s: %s",
            irqno, current->tid, current->name, strerr(ret));
        return ret;
    }
    pr_trace("sys_irq_listen: successfully listened irq %d by task tid=%ld name=%s",
        irqno, current->tid, current->name);
    return OK;
}

SYSCALL_DEFINE1(irq_unlisten, irq_t, irqno) {
    task_t* current = unwrap_null(current_task);
    pr_trace("sys_irq_unlisten: called by task tid=%ld name=%s to unlisten irq %d",
        current->tid, current->name, irqno);
    result_t ret = irq_unlisten(irqno, current);
    if (is_err(ret)) {
        pr_warn("sys_irq_unlisten: failed to unlisten irq %d by task tid=%ld name=%s: %s",
            irqno, current->tid, current->name, strerr(ret));
        return ret;
    }
    pr_trace("sys_irq_unlisten: successfully unlistened irq %d by task tid=%ld name=%s",
        irqno, current->tid, current->name);
    return OK;
}
