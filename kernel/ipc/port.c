#include "libs/prelude.h"
#include "kernel/ipc.h"
#include "kernel/mm/slab.h"
#include "kernel/task/processor.h"

// invariable: if a port exists in global port list,
// then the rx side task must be alive.
// when the rx side task dead, the port will be removed from this list.
// and all tx side tasks will be notified. if they are waiting to send message, they will be aborted.
static list_t port_list;
static kmem_cache_t port_cache;
static kmem_cache_t tport_cache;
static port_t next_pid = 1;

void
ipc_init(void) {
    list_init(&port_list);
    kmem_cache_create(&port_cache, "ipc_port", sizeof(ipc_port_t));
    kmem_cache_create(&tport_cache, "task_port", sizeof(task_port_t));
}

static port_t
alloc_pid() {
    while (p_get(next_pid) != NULL) {
        next_pid++;
        if (next_pid == PID_ANY) {
            panic("out of port ids");
        }
    }
    return next_pid;
}

// caller responsible for permission check
// when a tport is attached to a task, its permission cannot be changed later.
// too rigid, but enough for a simple IPC system.
static void
tp_attach(port_t pid, task_t* owner, port_flags_t privs) {
    ipc_port_t* port = unwrap_null(p_get(pid));
    task_port_t* tport;
    list_foreach(iter, &owner->port_list) {
        tport = list_entry(iter, task_port_t, node);
        assert_ne(tport->id, pid);
    }

    if ((privs & PORT_RECV) && (port->rx.task != NULL)) {
        panic("tp_attach: port %ld already has a receiver", pid);
    }

    tport = unwrap_null(kmem_cache_alloc(&tport_cache));
    tport->privs = privs;
    tport->id = pid;
    list_push_back(&owner->port_list, &tport->node);

    if (privs & PORT_RECV) {
        port->rx.task = owner;
    }
    if (privs & PORT_SEND) {
        list_push_back(&port->tx.tasks, &owner->node_port_tx);
    }
    trace("tp_attach: port %ld attached to task %ld with flags %lx",
        pid, owner->tid, privs);
}

// note that this function is extremely dangerous!
// if we detach a tport with recv right with notifying senders disabled,
// those senders may hang forever when trying to send message to this port.
// the reason for having this option is to support port transfer,
// where the recv right is transferred to another task immediately after detaching.
static void
tp_detach(
    port_t pid, 
    task_t* owner,
    port_flags_t flags,
    bool notify_senders
) {
    ipc_port_t* port = unwrap_null(p_get(pid));
    task_port_t* tport = unwrap_null(tp_get(owner, pid));
    
    if (tport->privs & PORT_RECV) {
        if (notify_senders) {
            // shall notify all senders here.
            warn("tp_detach: currently not notifying senders");
        }
        assert(!port->rx.is_receiving);
        port->rx.task = NULL;
    }
    if (tport->privs & PORT_SEND) {
        // a task waiting to send message cannot be detached.
        assert(!list_contains(&port->tx.waiting_tasks, &owner->node_port_wtx));
        list_remove(&owner->node_port_tx);
    }

    tport->privs &= ~port_privs(flags);
    if (tport->privs == 0) {
        // no need to maintain the tport if all privileges are removed
        trace("tp_detach: no privileges left for port %ld in task %ld, freeing tport",
            pid, owner->tid);
        list_remove(&tport->node);
        kmem_cache_free(&tport_cache, tport);
    }

    trace("tp_detach: port %ld detached from task %ld with flags %lx",
        pid, owner->tid, flags);
}


static void
ipc_port_init(ipc_port_t* port, port_t id, task_t* creator) {
    port->id = id;
    list_init(&port->tx.tasks);
    list_init(&port->tx.waiting_tasks);
    port->rx.task = NULL;
    port->rx.is_receiving = false;
    list_push_back(&port_list, &port->node);
    tp_attach(id, creator, PORT_RECV | PORT_SEND);
}


task_port_t*
tp_get(task_t* task, port_t pid) {
    list_foreach(iter, &task->port_list) {
        task_port_t* tport = list_entry(iter, task_port_t, node);
        if (tport->id == pid) {
            return tport;
        }
    }
    return NULL;
}

ipc_port_t*
p_get(port_t id) {
    list_foreach(iter, &port_list) {
        ipc_port_t* port = list_entry(iter, ipc_port_t, node);
        if (port->id == id) {
            return port;
        }
    }
    return NULL;
}

// note that this function should only be used at process boot time
// for those port transfers before message passing is available. (e.g. pm port, pns port, etc)
// most of the time ports' privileges are transferred via message passing.
isize
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

    ipc_port_t* port = unwrap_null(p_get(pid));
    task_port_t* tport = tp_get(ori, pid);
    if (tport == NULL) {
        warn("p_transfer: original owner task %ld has no such port %ld",
            ori->tid, pid);
        return -ERR_NOENT;
    }
    if ((tport->privs & flags) != port_privs(flags)) {
        warn("p_transfer: original owner task %ld has no enough privileges for port %ld transfer",
            ori->tid, pid);
        return -ERR_PERM;
    }
    if (tp_get(dst, pid) != NULL) {
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

    return 0;
}

// creator has both recv and send right.
// it may distribute these privileges later.
port_t
p_creat(port_t req_pid, task_t* owner) {
    if (req_pid == PID_ANY) {
        req_pid = alloc_pid();
    } else {
        // check if already exists
        if (p_get(req_pid) != NULL) {
            return (port_t)-ERR_EXIST;
        }
    }
    ipc_port_t* port = unwrap_null(kmem_cache_alloc(&port_cache));
    ipc_port_init(port, req_pid, owner);
    return port->id;
}

isize
p_close(port_t pid, task_t* task) {
    ipc_port_t* port = unwrap_null(p_get(pid));
    list_foreach_safe(iter, &task->port_list, next) {
        task_port_t* tport = list_entry(iter, task_port_t, node);
        if (tport->id == pid) {
            list_remove(&tport->node);
            if (tport->privs & PORT_RECV) {
                // shall notify all senders here.
                warn("p_close: currently not notifying senders");
            }
            if (tport->privs & PORT_SEND) {
                // assert(!list_contains(port->))   
            }

            kmem_cache_free(&tport_cache, tport);
            return 0;
        }
    }
    return -ERR_NOENT;
}

isize
p_send(const msg_hdr_t* msg) {
    // currently do not consider notifications
    port_t pid = msg->remote;
    ipc_port_t* port = p_get(pid);
    if (port == NULL) {
        warn("p_send: no such port %ld", pid);
        return -ERR_NOENT;
    }
    task_t* current = unwrap_null(current_task);
    task_port_t* tport = tp_get(current, pid);
    if (tport == NULL || !port_has_send(tport->privs)) {
        warn("p_send: current task has no send right for port %ld", pid);
        return -ERR_PERM;
    }
    
    memset(current->msg_buf, 0, MSG_MAX_SIZE);
    memcpy(current->msg_buf, msg, msg->size);
    
    list_push_back(&port->tx.waiting_tasks, &current->node_port_wtx);
    if (port->rx.is_receiving) {
        // wake up the receiver
        trace("p_send: receiver task %ld is waiting on port %ld, resuming it",
            port->rx.task->tid, pid);
        port->rx.is_receiving = false;
        task_resume(port->rx.task->tid);
    }
    trace("p_send: sender task %ld blocking on port %ld",
        current->tid, pid);
    task_block(current->tid);
    trace("p_send: sender task %ld resumed from port %ld",
        current->tid, pid);
    
    return 0;
}

isize
p_recv(msg_hdr_t* msg) {
    port_t local = msg->local;
    ipc_port_t* port = p_get(local);
    if (port == NULL) {
        warn("p_recv: no such port %ld", local);
        return -ERR_NOENT;
    }
    task_t* current = unwrap_null(current_task);
    task_port_t* tport = tp_get(current, local);
    if (tport == NULL || !port_has_recv(tport->privs)) {
        warn("p_recv: current task has no recv right for port %ld", local);
        return -ERR_PERM;
    }

    if (list_is_empty(&port->tx.waiting_tasks)) {
        // no sender currently.
        // block, and wait until sender is available.
        trace("p_recv: no sender for port %ld, blocking receiver task %ld",
            local, current->tid);
        port->rx.is_receiving = true;
        task_block(current->tid);
        // come back
        trace("p_recv: receiver task %ld resumed for port %ld",
            current->tid, local);
        assert_eq(port->rx.is_receiving, false);
        // now there must be a sender waiting.        
    }
    
    task_t* sender = list_entry(
        list_pop_front(&port->tx.waiting_tasks),
        task_t,
        node_port_wtx
    );
    msg_hdr_t *send_msg = (msg_hdr_t*)sender->msg_buf;
    port_t src = send_msg->remote; // this can be PID_INVALID for one-way message
    assert_eq(send_msg->remote, local);
    memcpy(msg, send_msg, send_msg->size);
    // need to do a swap of local and remote
    msg->local = local;
    msg->remote = src;

    task_resume(sender->tid);
    trace("p_recv: message received on port %ld by task %ld from task %ld",
        local, current->tid, sender->tid);
    return 0;
}