#include <libs/prelude.h>
#include <kernel/ipc.h>
#include <kernel/task/sched.h>
#include <kernel/task/processor.h>
#include <kernel/syscall.h>

SYSCALL_DEFINE1(p_creat, port_t, req_pid) {
    task_t* current = unwrap_null(current_task);
    port_t port;
    result_t ret = p_creat(req_pid, current, &port);
    if (is_err(ret)) {
        warn("sys_p_creat: failed to create port: %s",
            strerr(ret));
    } else {
        trace("sys_p_creat: task %d successfully created port %ld",
            current->tid, port);
    }
    return is_err(ret) ? ret : port;
}

SYSCALL_DEFINE1(p_close, port_t, pid) {
    task_t* current = unwrap_null(current_task);
    return p_close(pid, current);
}

SYSCALL_DEFINE2(
    p_send, 
    port_t, remote,
    const untyped_msg_t*, msg
) {
    task_t* current = unwrap_null(current_task);
    trace("sys_p_send: task %d sending message to port %ld",
        current->tid, remote);
    result_t ret = p_send(remote, msg);
    if (is_err(ret)) {
        warn("sys_p_send: failed to send message to port %ld: %s",
            remote, strerr(ret));
    } else {
        trace("sys_p_send: task %d successfully sent message to port %ld",
            current->tid, remote);
    }
    return ret;
}

SYSCALL_DEFINE2(
    p_notify,
    port_t, pid,
    const notif_t*, notif
) {
    task_t* current = unwrap_null(current_task);
    trace("sys_p_notify: task %d sending notification to port %ld",
        current->tid, pid);
    result_t ret = p_notify(pid, *notif);
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
    port_t, local, 
    untyped_msg_t*, msg,
    notif_t*, notif
) {
    task_t* current = unwrap_null(current_task);
    trace("sys_p_recv: task %d receiving message on port %ld",
        current->tid, local);
    result_t ret = p_recv(
        local,
        msg,
        notif
    );
    if (is_err(ret)) {
        warn("sys_p_recv: failed to receive message on port %ld: %s",
            local, strerr(ret));
    } else {
        trace("sys_p_recv: task %d successfully received message on port %ld",
            current->tid, local);
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

    ipc_port_t* port = NULL;
    result_t ret = p_get(pid, &port);
    if (is_err(ret)) {
        warn("sys_p_stat: failed to get port %ld: %s",
            pid, strerr(ret));
    } else {
        stat->id = pid;
        stat->owner = port->rx.task->tid;
        trace("sys_p_stat: task %d successfully queried stat of port %ld",
            current->tid, pid);
    }

    return ret;
}