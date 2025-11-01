#include "libs/prelude.h"
#include "kernel/ipc.h"
#include "kernel/task/sched.h"
#include "kernel/task/processor.h"
#include "kernel/syscall.h"

SYSCALL_DEFINE1(p_creat, port_t, req_pid) {
    task_t* current = unwrap_null(current_task);
    port_t ret = p_creat(req_pid, current);
    if (is_err(ret)) {
        warn("sys_p_creat: failed to create port: %s",
            strerr((isize)ret));
    } else {
        trace("sys_p_creat: task %d successfully created port %ld",
            current->tid, ret);
    }
    return ret;
}

SYSCALL_DEFINE1(p_close, port_t, pid) {
    task_t* current = unwrap_null(current_task);
    if (p_get(pid) == NULL) {
        warn("sys_p_close: no such port %ld", pid);
        return -ERR_NOENT;
    }
    isize ret = p_close(pid, current);
    if (is_err(ret)) {
        warn("sys_p_close: failed to close port %ld: %s",
            pid, strerr(ret));
    } else {
        trace("sys_p_close: task %d successfully closed port %ld",
            current->tid, pid);
    }
    return ret;
}

SYSCALL_DEFINE3(
    p_transfer,
    port_t, pid,
    tid_t, dst,
    port_flags_t, flags
) {
    task_t* current = unwrap_null(current_task);
    task_t* dst_task = task_get(dst);
    if (dst_task == NULL) {
        warn("sys_p_transfer: no such destination task %d", dst);
        return -ERR_NOENT;
    }
    if (p_get(pid) == NULL) {
        warn("sys_p_transfer: no such port %ld", pid);
        return -ERR_NOENT;
    }
    isize ret = p_transfer(pid, dst_task, current, flags);
    if (is_err(ret)) {
        warn("sys_p_transfer: failed to transfer port %ld to task %d: %s",
            pid, dst, strerr(ret));
    } else {
        trace("sys_p_transfer: task %d successfully transferred port %ld to task %d with flags %lx",
            current->tid, pid, dst, flags);
    }
    return ret;
}

SYSCALL_DEFINE1(p_send, msg_hdr_t*, msg) {
    todo()
}

SYSCALL_DEFINE1(p_recv, msg_hdr_t*, msg) {
    todo()
}