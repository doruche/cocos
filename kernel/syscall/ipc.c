#include <libs/prelude.h>
#include <kernel/ipc.h>
#include <kernel/task/sched.h>
#include <kernel/task/processor.h>
#include <kernel/syscall.h>

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
    if (tp_get(current, pid) == NULL) {
        warn("sys_p_close: current task %d has no such port %ld",
            current->tid, pid);
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

// so ugly...
// so many checks here...
SYSCALL_DEFINE3(
    p_transfer,
    port_t, pid,
    tid_t, dst,
    port_flags_t, flags
) {
    task_t* current = unwrap_null(current_task);
    task_t* dst_task = NULL;
    result_t ret = task_get(dst, &dst_task);
    if (is_err(ret)) {
        warn("sys_p_transfer: no such destination task %d", dst);
        return -ERR_NOENT;
    }
    if (dst_task == current) {
        warn("sys_p_transfer: cannot transfer port %ld to self", pid);
        return -ERR_INVAL;
    }
    if (p_get(pid) == NULL) {
        warn("sys_p_transfer: no such port %ld", pid);
        return -ERR_NOENT;
    }
    if (flags == 0) {
        warn("sys_p_transfer: no privileges specified for port %ld transfer", pid);
        return -ERR_INVAL;
    }
    if ((flags & ~(PORT_SEND | PORT_RECV | PORT_TRANSFER_DISCARD)) != 0) {
        warn("sys_p_transfer: invalid flags %lx for port %ld transfer", flags, pid);
        return -ERR_INVAL;
    }
    ret = p_transfer(pid, dst_task, current, flags);
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
    task_t* current = unwrap_null(current_task);
    trace("sys_p_send: task %d sending message to port %ld",
        current->tid, msg->remote);
    isize ret = p_send(msg);
    if (is_err(ret)) {
        warn("sys_p_send: failed to send message to port %ld: %s",
            msg->remote, strerr(ret));
    } else {
        trace("sys_p_send: task %d successfully sent message to port %ld",
            current->tid, msg->remote);
    }
    return ret;
}

SYSCALL_DEFINE2(
    p_notify,
    port_t, pid,
    notifications_t, notif
) {
    task_t* current = unwrap_null(current_task);
    trace("sys_p_notify: task %d sending notification to port %ld",
        current->tid, pid);
    isize ret = p_notify(pid, notif);
    if (is_err(ret)) {
        warn("sys_p_notify: failed to send notification to port %ld: %s",
            pid, strerr(ret));
    } else {
        trace("sys_p_notify: task %d successfully sent notification to port %ld",
            current->tid, pid);
    }
    return ret;
}

SYSCALL_DEFINE3(
    p_recv, 
    msg_hdr_t*, msg,
    notifications_t*, notif,
    notifications_t, mask
) {
    task_t* current = unwrap_null(current_task);
    trace("sys_p_recv: task %d receiving message on port %ld",
        current->tid, msg->local);
    isize ret = p_recv(msg, notif, mask);
    if (is_err(ret)) {
        warn("sys_p_recv: failed to receive message on port %ld: %s",
            msg->local, strerr(ret));
    } else {
        trace("sys_p_recv: task %d successfully received message on port %ld",
            current->tid, msg->local);
    }
    return ret;
}

SYSCALL_DEFINE2(
    p_stat,
    port_t, pid,
    p_stat_t*, stat
) {
    task_t* current = unwrap_null(current_task);
    trace("sys_p_stat: task %d querying stat of port %ld",
        current->tid, pid);
    task_port_t* tport = tp_get(current, pid);
    if (tport == NULL) {
        warn("sys_p_stat: no such port %ld in current task %d",
            pid, current->tid);
        return -ERR_NOENT;
    }
    
    stat->id = pid;
    stat->privs = port_privs(tport->privs);

    return 0;
}