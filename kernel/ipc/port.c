#include <libs/prelude.h>
#include <kernel/ipc.h>
#include <kernel/mm/slab.h>
#include <kernel/task/processor.h>

/* 
 * invariable: if a port exists in global port list,
 * then the rx side task must be alive.
 * when the rx side task dead, the port will be removed from this list.
 * and all tx side tasks will be notified. if they are waiting to send message, they will be aborted.
 */

static list_t port_list;
static kmem_cache_t port_cache;
static kmem_cache_t tport_cache;
static kmem_cache_t knotif_cache;
static port_t next_pid = PID_PM;

void
ipc_init(void) {
    list_init(&port_list);
    kmem_cache_create(&port_cache, "ipc_port", sizeof(ipc_port_t));
    kmem_cache_create(&tport_cache, "task_port", sizeof(task_port_t));
    kmem_cache_create(&knotif_cache, "knotif", sizeof(knotif_t));
}

static port_t
alloc_pid() {
    ipc_port_t* placeholder;
    while (p_get(next_pid, &placeholder) == OK) {
        next_pid++;
        if (next_pid == PID_ANY) {
            panic("out of port ids");
        }
    }
    return next_pid;
}

// when a tport is attached to a task, its permission cannot be changed later.
// too rigid, but enough for a simple IPC system.
result_t
tp_attach(port_t pid, task_t* owner, port_flags_t privs) {
    result_t ret;
    ipc_port_t* port = NULL;
    task_port_t* tport = NULL;
    unwrap_err(p_get(pid, &port));
    assert(is_err(tp_get(owner, pid, &tport))); // should not exist

    tport = unwrap_null(kmem_cache_alloc(&tport_cache));
    tport->privs = privs;
    tport->id = pid;
    list_push_back(&owner->port_list, &tport->node);


    if (privs & PORT_RECV) {
        if (port->rx.task != NULL) {
            warn("tp_attach: port %ld already has a receiver task %ld",
                pid, port->rx.task->tid);
            ret = -ERR_EXIST;
            goto err;
        }
        port->rx.task = owner;
    }
    if (privs & PORT_SEND) {
        port->tx_rc++;
    }
    trace("tp_attach: port %ld attached to task %ld with flags %lx"
        " current tx_rc=%ld",
        pid, owner->tid, privs, port->tx_rc);

    return OK;

err:
    if (tport != NULL) {
        list_remove(&tport->node);
        kmem_cache_free(&tport_cache, tport);
    }
    return ret;
}

/*
 * note that this function is EXTREMELY DANGEROUS.
 * if we detach a tport with recv right and close disabled,
 * those senders may hang forever when trying to send message to this port.
 * the reason for having this option is to support port transfer,
 * where the recv right is transferred to another task immediately after detaching.
 */
static void
tp_detach(
    port_t pid, 
    task_t* owner,
    port_flags_t flags,
    bool close
) {
    ipc_port_t* port = NULL;
    task_port_t* tport = NULL;
    unwrap_err(p_get(pid, &port));
    unwrap_err(tp_get(owner, pid, &tport));


    flags = tport->privs & flags;

    if (port_has_send(flags)) {
        // a task waiting to send message cannot be detached.
        trace("tp_detach: removing tx right on port %ld from task %ld",
            pid, owner->tid);
        assert(!list_contains(&port->wtx, &owner->node_port_wtx));
        port->tx_rc--;
    }

    if (port_has_recv(flags)) {
        trace("tp_detach: removing rx right on port %ld from task %ld",
            pid, owner->tid);
        assert(!port->rx.is_receiving);
        port->rx.task = NULL;
        if (close) {
            // only notify blocked senders here.
            // note that we adopt a lazy free strategy for ports.
            // even though we know the port is dead now,
            // we do not remove senders' tport.
            // it will be done when they call p_close later.
            port->dead = true;
            list_foreach_safe(iter, &port->wtx, next) {
                task_t* sender = list_entry(iter, task_t, node_port_wtx);
                list_remove(&sender->node_port_wtx);
                
                knotif_t* knotif = unwrap_null(kmem_cache_alloc(&knotif_cache));
                knotif->notif.type = NOTIF_ABORTED;
                knotif->notif.payload.port_aborted = pid;
                list_push_back(&sender->notif_list, &knotif->node);

                task_resume(sender->tid);
                trace("tp_detach: notifying sender task %ld blocked on port %ld",
                    sender->tid, pid);
            }
        }
    }

    tport->privs &= ~port_privs(flags);
    if (tport->privs == 0) {
        // no need to maintain the tport if all privileges are removed
        trace("tp_detach: no privileges left on port %ld in task %ld, freeing tport",
            pid, owner->tid);
        list_remove(&tport->node);
        kmem_cache_free(&tport_cache, tport);
    }

    if (port->tx_rc == 0 && port->dead) {
        info("tp_detach: port %ld has no tx_rc and is dead, freeing port",
            pid);
        list_remove(&port->node);
        assert(port->rx.task == NULL);
        assert(list_is_empty(&port->wtx));
        kmem_cache_free(&port_cache, port);
    }

    trace("tp_detach: port %ld detached from task %ld with flags %lx",
        pid, owner->tid, flags);
}

static void
ipc_port_init(ipc_port_t* port, port_t id, task_t* creator) {
    port->id = id;
    list_init(&port->wtx);
    port->rx.task = NULL;
    port->rx.is_receiving = false;
    port->dead = false;
    port->tx_rc = 0;
    list_push_back(&port_list, &port->node);
    unwrap_err(tp_attach(id, creator, PORT_RECV | PORT_SEND));
}


result_t
tp_get(task_t* task, port_t pid, task_port_t** out) {
    list_foreach(iter, &task->port_list) {
        task_port_t* tport = list_entry(iter, task_port_t, node);
        if (tport->id == pid) {
            *out = tport;
            return OK;
        }
    }
    return -ERR_NOENT;
}

result_t
p_get(port_t id, ipc_port_t** out) {
    list_foreach(iter, &port_list) {
        ipc_port_t* port = list_entry(iter, ipc_port_t, node);
        if (port->id == id) {
            *out = port;
            return OK;
        }
    }
    return -ERR_NOENT;
}

static bool
task_own_port(port_t pid, port_flags_t privs, task_t* task) {
    task_port_t* tport = NULL;
    if (is_err(tp_get(task, pid, &tport))) {
        return false;
    }
    if ((tport->privs & privs) != port_privs(privs)) {
        return false;
    }
    return true;
}

// note that this function should only be used directly at process boot stage
// for those port transfers before message passing is available. (e.g. pns port)
// most of the time ports' privileges are transferred via message passing.
result_t
p_transfer(
    port_t pid,
    task_t* dst,
    task_t* ori,
    port_flags_t flags
) {
    assert_ne(dst, ori);
    if (port_has_recv(flags) && ((flags & PORT_TRANSFER_DISCARD) == 0)) {
        warn("p_transfer: cannot transfer recv right without discarding from original owner");
        return -ERR_INVAL;
    }
    task_port_t* tport = NULL;
    if (is_err(tp_get(ori, pid, &tport))) {
        warn("p_transfer: original owner task %ld has no such port %ld",
            ori->tid, pid);
        return -ERR_NOENT;
    }
    if ((tport->privs & flags) != port_privs(flags)) {
        warn("p_transfer: original owner task %ld has no enough privileges on port %ld transfer",
            ori->tid, pid);
        return -ERR_PERM;
    }
    task_port_t* dst_tport = NULL;
    if (tp_get(dst, pid, &dst_tport) == OK) {
        warn("p_transfer: destination task %ld already has port %ld",
            dst->tid, pid);
        return -ERR_EXIST;
    }

    if (flags & PORT_TRANSFER_DISCARD) {
        tp_detach(pid, ori, flags, false);
    }
    tp_attach(pid, dst, port_privs(flags));

    trace("p_transfer: port %ld transferred from task %ld to task %ld with flags %lx",
        pid, ori->tid, dst->tid, flags);

    return OK;
}

// creator has both recv and send right.
// it may distribute these privileges later.
result_t
p_creat(port_t req_pid, task_t* owner, port_t* out) {
    if (req_pid == PID_ANY) {
        req_pid = alloc_pid();
    } else {
        // check if already exists
        ipc_port_t* existing;
        if (p_get(req_pid, &existing) == OK) {
            return (port_t)-ERR_EXIST;
        }
    }
    ipc_port_t* port = unwrap_null(kmem_cache_alloc(&port_cache));
    ipc_port_init(port, req_pid, owner);

    *out = req_pid;
    trace("p_creat: port %ld created by task %ld",
        req_pid, owner->tid);
    return OK;
}

result_t
p_close(port_t pid, task_t* task) {
    task_port_t* tport = NULL;
    if (is_err(tp_get(task, pid, &tport))) {
        warn("p_close: task %ld has no such port %ld",
            task->tid, pid);
        return -ERR_NOENT;
    }
    tp_detach(pid, task, tport->privs, true);

    return OK;
}

// only called by user tasks.
result_t
p_send(const msg_hdr_t* msg) {
    port_t remote = msg->remote;
    ipc_port_t* port = NULL;
    if (is_err(p_get(remote, &port))) {
        warn("p_send: no such port %ld", remote);
        return -ERR_NOENT;
    }

    task_t* current = unwrap_null(current_task);
    task_port_t* tport = NULL;
    if (is_err(tp_get(current, remote, &tport))) {
        warn("p_send: current task has no such port %ld", remote);
        return -ERR_NOENT;
    }
    if (!port_has_send(tport->privs)) {
        warn("p_send: current task has no send right on port %ld", remote);
        return -ERR_PERM;
    }
    if (port_has_recv(tport->privs)) {
        warn("p_send: cannot send to receive-owning port %ld", remote);
        return -ERR_INVAL;
    }
    if (port->dead) {
        warn("p_send: port %ld is dead", remote);
        return -ERR_ABORT;
    }
    if (msg->aux_xfer.port != PID_INVALID &&
        msg->aux_xfer.flags != 0) {
        if (msg->remote == msg->aux_xfer.port) {
            warn("p_send: cannot transfer the same port %ld being sent to",
                msg->aux_xfer.port);
            return -ERR_INVAL;
        }
        if (!task_own_port(msg->aux_xfer.port, msg->aux_xfer.flags, current)) {
            warn("p_send: current task does not have port %ld with privs %lx",
                msg->aux_xfer.port, msg->aux_xfer.flags);
            return -ERR_PERM;
        }
        if (task_own_port(msg->aux_xfer.port, 0, port->rx.task)) {
            warn("p_send: receiver task %ld already owns port %ld",
                port->rx.task->tid, msg->aux_xfer.port);
            return -ERR_EXIST;
        }
        // transfer the port
        if (is_err(p_transfer(
            msg->aux_xfer.port,
            port->rx.task,
            current,
            msg->aux_xfer.flags
        ))) {
            panic("p_send: port transfer failed unexpectedly");
        }
    }
    
    memcpy(current->msg_buf, msg, MSG_MAX_SIZE);

    list_push_back(&port->wtx, &current->node_port_wtx);
    if (port->rx.is_receiving) {
        // wake up the receiver
        trace("p_send: receiver task %ld is waiting on port %ld, resuming it",
            port->rx.task->tid, remote);
        port->rx.is_receiving = false;
        task_resume(port->rx.task->tid);
    }
    trace("p_send: sender task %ld blocking on port %ld",
        current->tid, remote);
    task_block(current->tid);
    
    list_foreach_safe(iter, &current->notif_list, next) {
        knotif_t* knotif = list_entry(iter, knotif_t, node);
        if (knotif->notif.type == NOTIF_ABORTED &&
            knotif->notif.payload.port_aborted == remote) {
            // aborted
            list_remove(&knotif->node);
            kmem_cache_free(&knotif_cache, knotif);
            warn("p_send: send from task %ld to port %ld aborted",
                current->tid, remote);
            return -ERR_ABORT;
        }
    }

    trace("p_send: sender task %ld resumed from port %ld",
        current->tid, remote);
    
    return OK;
}

static result_t
p_notify_inner(port_t pid, notif_t notif, bool perm_check) {
    ipc_port_t* port = NULL;
    if (is_err(p_get(pid, &port))) {
        warn("p_notify: no such port %ld", pid);
        return -ERR_NOENT;
    }
    if (perm_check) {
        task_t* current = unwrap_null(current_task);
        task_port_t* tport = NULL;
        if (is_err(tp_get(current, pid, &tport))) {
            warn("p_notify: current task has no such port %ld", pid);
            return -ERR_NOENT;
        }
        if (!port_has_send(tport->privs)) {
            warn("p_notify: current task has no send right on port %ld", pid);
            return -ERR_PERM;
        }
        if (port_has_recv(tport->privs)) {
            warn("p_notify: cannot notify to receive-owning port %ld", pid);
            return -ERR_INVAL;
        }
    }
    if (port->dead) {
        warn("p_notify: port %ld is dead", pid);
        return -ERR_NOENT;
    }

    task_t* rx_task = port->rx.task;
    knotif_t* knotif = unwrap_null(kmem_cache_alloc(&knotif_cache));
    knotif->notif = notif;
    list_push_back(&rx_task->notif_list, &knotif->node);
    
    if (port->rx.is_receiving) {
        trace("p_notify: receiver task %ld is waiting on port %ld, "
            "resuming it for notification",
            rx_task->tid, pid);
        port->rx.is_receiving = false;
        task_resume(rx_task->tid);
    }
    if (perm_check) {
        trace("p_notify: sender task %ld sent notification on port %ld",
            current_task->tid, pid);
    }
    return OK;
}

result_t
p_notify(port_t pid, notif_t notif) {
    return p_notify_inner(pid, notif, true);
}

result_t
p_knotify(port_t pid, notif_t notif) {
    return p_notify_inner(pid, notif, false);
}

static result_t
try_recv(ipc_port_t* port, msg_hdr_t* msg, notif_t* notif) {
    task_t* current = unwrap_null(current_task);

    if (!list_is_empty(&port->wtx)) {
        task_t* sender = list_entry(
            list_pop_front(&port->wtx),
            task_t,
            node_port_wtx
        );
        msg_hdr_t *send_msg = (msg_hdr_t*)sender->msg_buf;
        assert_eq(send_msg->remote, port->id);
        memcpy(msg, send_msg, MSG_MAX_SIZE);
        task_resume(sender->tid);
        trace("try_recv: message received on port %ld by task %ld from task %ld",
            port->id, current->tid, sender->tid);
        return OK;
    }

    if (!list_is_empty(&current->notif_list)) {
        knotif_t* knotif = list_entry(
            list_pop_front(&current->notif_list),
            knotif_t,
            node
        );
        *notif = knotif->notif;
        kmem_cache_free(&knotif_cache, knotif);
        trace("try_recv: notification received on port %ld by task %ld: %lx",
            port->id, current->tid, notif->type);
        return OK;
    }

    return -ERR_NOENT;
}

result_t
p_recv(msg_hdr_t* msg, notif_t* notif) {
    port_t local = msg->local;
    task_t* current = unwrap_null(current_task);
    
    if (local == PID_ANY) {
        bool found = false;
        list_foreach(iter, &current->port_list) {
            task_port_t* tport = list_entry(iter, task_port_t, node);
            if (port_has_recv(tport->privs)) {
                ipc_port_t* port = NULL;
                unwrap_err(p_get(tport->id, &port));
                if (try_recv(port, msg, notif) == OK) {
                    found = true;
                    break;
                }
            }
        }
        if (found) {
            return OK;
        }
        
        trace("p_recv: no message or notification on any port, blocking receiver task %ld",
            current->tid);
        list_foreach(iter, &current->port_list) {
            task_port_t* tport = list_entry(iter, task_port_t, node);
            if (port_has_recv(tport->privs)) {
                ipc_port_t* port = NULL;
                unwrap_err(p_get(tport->id, &port));
                port->rx.is_receiving = true;
                trace("p_recv: task %ld listening on port %ld",
                    current->tid, tport->id);
            }
        }
        task_block(current->tid);
        // come back
        trace("p_recv: receiver task %ld resumed from any port",
            current->tid);
        // note that we may have multiple ports with available messages/notifications now.
        // just pick the first one. and reset all other ports' is_receiving flag.
        list_foreach(iter, &current->port_list) {
            task_port_t* tport = list_entry(iter, task_port_t, node);
            if (port_has_recv(tport->privs)) {
                ipc_port_t* port = NULL;
                unwrap_err(p_get(tport->id, &port));
                if (try_recv(port, msg, notif) == OK) {
                    assert_eq(port->rx.is_receiving, false);
                    trace("p_recv: message/notification received on port %ld by task %ld",
                        port->id, current->tid);
                    // reset other ports' is_receiving flag
                    list_foreach(iter2, &current->port_list) {
                        task_port_t* tport2 = list_entry(iter2, task_port_t, node);
                        if (tport2->id == tport->id) {
                            continue;
                        }
                        if (port_has_recv(tport2->privs)) {
                            ipc_port_t* port2 = NULL;
                            unwrap_err(p_get(tport2->id, &port2));
                            if (!port2->rx.is_receiving) {
                                trace("p_recv: during any-port recv, port %ld has also been"
                                " send a message/notification.", port2->id);
                            } else {
                                port2->rx.is_receiving = false;
                            }
                        }
                    }
                    return OK;
                }
            }
        }

        panic("p_recv: receiver task %ld resumed from any port but no message or notification found",
            current->tid);
    } else {
        ipc_port_t* port = NULL;
        if (is_err(p_get(local, &port))) {
            warn("p_recv: no such port %ld", local);
            return -ERR_NOENT;
        }
        task_port_t* tport = NULL;
        if (is_err(tp_get(current, local, &tport))) {
            warn("p_recv: current task has no such port %ld", local);
            return -ERR_NOENT;
        }
        if (!port_has_recv(tport->privs)) {
            warn("p_recv: current task has no recv right on port %ld", local);
            return -ERR_PERM;
        }

        if (try_recv(port, msg, notif) == OK) {
            return OK;
        }

        // oops. seems no message or notification available.
        // block the receiver.
        trace("p_recv: no message or notification on port %ld, blocking receiver task %ld",
            local, current->tid);
        port->rx.is_receiving = true;
        task_block(current->tid);
        // come back
        trace("p_recv: receiver task %ld resumed on port %ld",
            current->tid, local);
        assert_eq(port->rx.is_receiving, false);

        if (try_recv(port, msg, notif) == OK) {
            return OK;
        }
    }

    panic("p_recv: receiver task %ld resumed on port %ld but no message or notification found",
        current->tid, local);
}

void
task_ipc_cleanup(task_t* task) {
    list_foreach_safe(iter, &task->port_list, next) {
        trace("task_ipc_cleanup: closing port %ld for task %ld",
            list_entry(iter, task_port_t, node)->id,
            task->tid);
        task_port_t* tport = list_entry(iter, task_port_t, node);
        unwrap_err(p_close(tport->id, task));
    }
    list_foreach_safe(iter, &task->notif_list, next) {
        knotif_t* knotif = list_entry(iter, knotif_t, node);
        warn("task_ipc_cleanup: discarding notification of type %lx for task %ld",
            knotif->notif.type, task->tid);
        list_remove(&knotif->node);
        kmem_cache_free(&knotif_cache, knotif);
    }
}
