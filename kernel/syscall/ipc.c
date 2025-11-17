#include <libs/prelude.h>
#include <kernel/ipc.h>
#include <kernel/task/sched.h>
#include <kernel/task/processor.h>
#include <kernel/syscall.h>

SYSCALL_DEFINE4(
    ipc,
    tid_t, send_to,
    tid_t, recv_from,
    msg_t*, msg,
    ipc_flags_t, flags
) {
    if (flags & IPC_KERN) {
        pr_warn("sys_ipc: user task trying to use IPC_KERN flag");
        return -ERR_PERM;
    }
    if (send_to == current_task->tid ||
    recv_from == current_task->tid) {
        pr_warn("sys_ipc: task tid=%ld name=%s trying to ipc with itself",
            current_task->tid, current_task->name);
        return -ERR_INVAL;
    }

    task_t* send_task = NULL;
    if (flags & IPC_SEND) {
        result_t ret = task_get(send_to, &send_task);
        if (is_err(ret)) {
            pr_warn("sys_ipc: no such task %ld", send_to);
            return ret;
        }
    }

    return ipc(
        send_task,
        recv_from,
        msg,
        flags
    );
}

SYSCALL_DEFINE2(
    notify,
    tid_t, dst,
    notif_t, notifs
) {
    task_t* dst_task = NULL;
    result_t ret = task_get(dst, &dst_task);
    if (is_err(ret)) {
        pr_warn("sys_notify: no such task %ld", dst);
        return ret;
    }
    return notify(dst_task, notifs);
}
