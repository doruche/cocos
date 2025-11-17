#include <libs/prelude.h>
#include <kernel/ipc.h>
#include <kernel/task/sched.h>
#include <kernel/task/processor.h>

result_t
notify(task_t* dst, notif_t notifs) {
    if (dst->state == T_ZOMBIE) {
        pr_warn("notify: cannot notify zombie task tid=%ld name=%s",
            dst->tid, dst->name);
        return -ERR_DEAD_TASK;
    }
    dst->notifs |= notifs;
    if (dst->listen_on == IPC_OPEN && dst->state == T_BLOCKED) {
        dst->msg.type = MSG_NOTIF;
        dst->msg.src = TID_KERNEL;
        dst->msg.notifs = dst->notifs;
        dst->notifs = 0;
        task_resume(dst->tid);
        pr_trace("notify: delivered notification %b to task tid=%ld name=%s",
            dst->msg.notifs, dst->tid, dst->name);
    } else {
        pr_trace("notify: queued notification %b for task tid=%ld name=%s",
            notifs, dst->tid, dst->name);
    }
    return OK;
}

result_t
ipc(
    task_t* send_to,
    tid_t recv_from,
    msg_t* msg,
    ipc_flags_t flags
) {
    task_t* current = unwrap_null(current_task);
    assert_eq(current->listen_on, TID_INVALID);
    
    /* send */
    if (flags & IPC_SEND) {
        assert(send_to != NULL);
        if (send_to->state == T_ZOMBIE) {
            pr_warn("ipc: cannot do ipc to zombie task tid=%ld name=%s",
                send_to->tid, send_to->name);
            return -ERR_DEAD_TASK;
        }
        bool recv_ready = 
            send_to->state == T_BLOCKED &&
            (send_to->listen_on == IPC_OPEN || 
            send_to->listen_on == current->tid);
        pr_notify("ipc: target listen_on = %ld",
            send_to->listen_on);
        if (!recv_ready) {
            if (flags & IPC_NONBLOCK) {
                pr_trace("ipc: nonblock send failed: tid %ld %s -> tid %ld %s",
                    current->tid, current->name, send_to->tid, send_to->name);
                return -ERR_WOULD_BLOCK;
            }
            
            list_push_back(&send_to->sender_list, &current->node_sender);
            memcpy(&current->msg, msg, sizeof(msg_t));
            current->msg.src = (flags & IPC_KERN) ? TID_KERNEL : current->tid;
            pr_trace("ipc: blocked sender task tid=%ld name=%s sending to tid=%ld name=%s",
                current->tid, current->name, send_to->tid, send_to->name);
            unwrap_err(task_block(current->tid));

            if (current->notifs & NOTIF_IPC_ABORT) {
                current->notifs &= ~NOTIF_IPC_ABORT;
                pr_trace("ipc: send aborted for task tid=%ld name=%s",
                    current->tid, current->name);
                return -ERR_ABORT;
            }
        } else {
            /* sender already waiting. direct delivery */
            memcpy(&send_to->msg, msg, sizeof(msg_t));
            send_to->msg.src = (flags & IPC_KERN) ? TID_KERNEL : current->tid;
            unwrap_err(task_resume(send_to->tid));
        }
    }    

    /* recv */
    if (flags & IPC_RECV) {
        if (recv_from == IPC_OPEN && current->notifs != 0) {
            msg->type = MSG_NOTIF;
            msg->src = TID_KERNEL;
            msg->notifs = current->notifs;
            current->notifs = 0;
            pr_trace("ipc: delivered notification %b to task tid=%ld name=%s",
                msg->notifs, current->tid, current->name);
        } else {
            if (flags & IPC_NONBLOCK) {
                pr_trace("ipc: nonblock recv failed: tid %ld %s",
                    current->tid, current->name);
                return -ERR_WOULD_BLOCK;
            }

            /* try to wake up a sender if any */
            list_elem_t* node_sender = 
                list_pop_front(&current->sender_list);
            if (node_sender != NULL) {
                task_t* sender = list_entry(
                    node_sender,
                    task_t,
                    node_sender
                );
                memcpy(msg, &sender->msg, sizeof(msg_t));
                unwrap_err(task_resume(sender->tid));
                pr_trace("ipc: received message from tid=%ld name=%s to tid=%ld name=%s",
                    sender->tid, sender->name, current->tid, current->name);
            } else {
                if (flags & IPC_NONBLOCK) {
                    pr_trace("ipc: nonblock recv failed: tid %ld %s",
                        current->tid, current->name);
                    return -ERR_WOULD_BLOCK;
                }
                current->listen_on = recv_from;
                pr_trace("ipc: blocked receiver task tid=%ld name=%s waiting for tid=%ld",
                    current->tid, current->name, recv_from);
                unwrap_err(task_block(current->tid));
                current->listen_on = TID_INVALID;
                memcpy(msg, &current->msg, sizeof(msg_t));
                pr_trace("ipc: received message to tid=%ld name=%s",
                    current->tid, current->name);
            }
        }
    }

    return OK;
}
