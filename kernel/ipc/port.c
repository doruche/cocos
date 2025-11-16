#include <libs/prelude.h>
#include <kernel/ipc.h>
#include <kernel/mm/slab.h>
#include <kernel/task/processor.h>

static list_t port_list;
static kmem_cache_t port_cache;
static kmem_cache_t knotif_cache;
static port_t next_pid = PID_PM;

void
ipc_init(void) {
    list_init(&port_list);
    kmem_cache_create(&port_cache, "ipc_port", sizeof(ipc_port_t));
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


static void
ipc_port_init(ipc_port_t* port, port_t id, task_t* creator) {
    port->id = id;
    list_init(&port->wtx);
    port->rx.task = creator;
    port->rx.is_receiving = false;
    list_push_back(&port_list, &port->node);
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

result_t
p_creat(port_t req_pid, task_t* owner, port_t* out) {
    if (req_pid == PID_ANY) {
        req_pid = alloc_pid();
    } else {
        /* check if already exists */
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
    ipc_port_t* port = NULL;
    if (is_err(p_get(pid, &port))) {
        warn("p_close: no such port %ld", pid);
        return -ERR_NOENT;
    }
    if (port->rx.task != task) {
        warn("p_close: task %ld is not the owner of port %ld",
            task->tid, pid);
        return -ERR_PERM;
    }

    list_foreach_safe(iter, &port->wtx, next) {
        task_t* sender = list_entry(iter, task_t, node_port_wtx);
        list_remove(&sender->node_port_wtx);

        k_notify(sender, (notif_t){
            .payload.port_aborted = pid,
            .type = NOTIF_ABORTED
        });

        unwrap_err(task_resume(sender->tid));
        trace("p_close: sender task %ld on port %ld aborted due to port close",
            sender->tid, pid);
    }

    list_remove(&port->node);
    kmem_cache_free(&port_cache, port);
    trace("p_close: port %ld closed by task %ld",
        pid, task->tid);

    return OK;
}

result_t
p_send(
    port_t remote,
    const untyped_msg_t* msg
) {
    ipc_port_t* port = NULL;
    if (is_err(p_get(remote, &port))) {
        warn("p_send: no such port %ld", remote);
        return -ERR_NOENT;
    }

    task_t* current = unwrap_null(current_task);
    memcpy(current->msg_buf, msg, MSG_SIZE);

    list_push_back(&port->wtx, &current->node_port_wtx);
    if (port->rx.is_receiving) {
        /* wake up the receiver */
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
            /* aborted */
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
p_notify(port_t pid, notif_t notif) {
    ipc_port_t* port = NULL;
    if (is_err(p_get(pid, &port))) {
        warn("p_notify: no such port %ld", pid);
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
    
    trace("p_notify: notification of type %lx sent to task %ld on port %ld",
        notif.type, rx_task->tid, pid);

    return OK;
}

result_t
k_notify(task_t* task, notif_t notif) {
    knotif_t* knotif = unwrap_null(kmem_cache_alloc(&knotif_cache));
    knotif->notif = notif;
    list_push_back(&task->notif_list, &knotif->node);
    
    trace("k_notify: notification of type %lx sent to task %ld",
        notif.type, task->tid);
    
    return OK;
}

static result_t
try_recv(ipc_port_t* port, untyped_msg_t* msg, notif_t* notif) {
    task_t* current = unwrap_null(current_task);

    if (!list_is_empty(&port->wtx)) {
        task_t* sender = list_entry(
            list_pop_front(&port->wtx),
            task_t,
            node_port_wtx
        );
        memcpy(msg, sender->msg_buf, MSG_SIZE);
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
p_recv(
    port_t local,
    untyped_msg_t* msg, 
    notif_t* notif
) {
    task_t* current = unwrap_null(current_task);
    
    if (local == PID_ANY) {
        bool found = false;
        list_foreach(iter, &port_list) {
            ipc_port_t* port = list_entry(iter, ipc_port_t, node);
            if (port->rx.task == current) {
                if (try_recv(port, msg, notif) == OK) {
                    trace("p_recv: message/notification received on port %ld by task %ld",
                        port->id, current->tid);
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
        
        list_foreach(iter, &port_list) {
            ipc_port_t* port = list_entry(iter, ipc_port_t, node);
            if (port->rx.task == current) {
                port->rx.is_receiving = true;
            }
        }
        task_block(current->tid);
        
        /* come back */
        trace("p_recv: receiver task %ld resumed from any port",
            current->tid);
        
        /* 
         * note that we may have multiple ports with available messages/notifications now.
         * just pick the first one. and reset all other ports' is_receiving flag.
         */
        list_foreach(iter, &port_list) {
            ipc_port_t* port = list_entry(iter, ipc_port_t, node);
            if (port->rx.task == current) {
                if (!found) {
                    if (try_recv(port, msg, notif) == OK) {
                        assert_eq(port->rx.is_receiving, false);
                        trace("p_recv: message/notification received on port %ld by task %ld",
                            port->id, current->tid);
                        found = true;
                    }
                }
                port->rx.is_receiving = false;
            }
        }
        if (found) {
            return OK;
        }

    } else {
        ipc_port_t* port = NULL;
        if (is_err(p_get(local, &port))) {
            warn("p_recv: no such port %ld", local);
            return -ERR_NOENT;
        }
        if (port->rx.task != current) {
            warn("p_recv: task %ld is not the owner of port %ld",
                current->tid, local);
            return -ERR_PERM;
        }
 
        if (try_recv(port, msg, notif) == OK) {
            return OK;
        }

        /* 
         * oops. seems no message or notification available.
         * block the receiver.
         */
        trace("p_recv: no message or notification on port %ld, blocking receiver task %ld",
            local, current->tid);
        port->rx.is_receiving = true;
        task_block(current->tid);

        /* come back */
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
    list_foreach_safe(iter, &port_list, next) {
        ipc_port_t* port = list_entry(iter, ipc_port_t, node);
        if (port->rx.task == task) {
            /* close the port */
            unwrap_err(p_close(port->id, task));
        }
    }
    list_foreach_safe(iter, &task->notif_list, next) {
        knotif_t* knotif = list_entry(iter, knotif_t, node);
        warn("task_ipc_cleanup: discarding notification of type %lx for task %ld",
            knotif->notif.type, task->tid);
        list_remove(&knotif->node);
        kmem_cache_free(&knotif_cache, knotif);
    }
}

void
ipc_port_dump(void) {
    list_foreach(iter, &port_list) {
        ipc_port_t* port = list_entry(iter, ipc_port_t, node);
        info("port id=%ld owner=%ld is_receiving=%d wtx_count=%ld",
            port->id,
            port->rx.task->tid,
            port->rx.is_receiving,
            list_length(&port->wtx
        ));
    }
}
