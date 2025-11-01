#include "libs/prelude.h"
#include "kernel/ipc.h"
#include "kernel/mm/slab.h"
#include "libs/string.h"
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

static void
ipc_port_init(ipc_port_t* port, port_t id) {
    port->id = id;
    port->rx = NULL;
    list_init(&port->tx_list);
    list_push_back(&port_list, &port->node);
}

static task_port_t*
find_tport(task_t* task, port_t pid) {
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

// caller responsible for permission check
// when a tport is attached to a task, its permission cannot be changed later.
isize
p_attach(port_t pid, task_t* owner, port_flags_t privs) {
    ipc_port_t* port = unwrap_null(p_get(pid));
    task_port_t* tport;
    list_foreach(iter, &owner->port_list) {
        tport = list_entry(iter, task_port_t, node);
        if (tport->id == pid) {
            return -ERR_EXIST;
        }
    }
   
    tport = unwrap_null(kmem_cache_alloc(&tport_cache));
    tport->privs = privs;
    tport->id = pid;
    list_push_back(&owner->port_list, &tport->node);
    if (privs & PORT_RECV) {
        port->rx = owner;
    } 
    trace("p_attach: port %ld attached to task %ld with flags %lx",
        pid, owner->tid, privs);

    return 0;
}

isize
p_transfer(
    port_t pid,
    task_t* dst,
    task_t* ori,
    port_flags_t flags   
) {
    ipc_port_t* port = unwrap_null(p_get(pid));
    task_port_t* tport = find_tport(ori, pid);
    if (tport == NULL) {
        return -ERR_NOENT;
    }
    if ((tport->privs & flags) != flags) {
        return -ERR_PERM;
    }
    if (find_tport(dst, pid) != NULL) {
        return -ERR_EXIST;
    }

    // create new tport for dst
    task_port_t* new_tport = unwrap_null(kmem_cache_alloc(&tport_cache));
    new_tport->id = pid;
    new_tport->privs = port_privs(flags);
    list_push_back(&dst->port_list, &new_tport->node);

    // update port's rx/tx list
    if (flags & PORT_RECV) {
        port->rx = dst;
        // only one rx can exist at the same time.
        list_remove(&tport->node);
    }
    if (flags & PORT_SEND) {
        if (flags & PORT_TRANSFER_DISCARD && list_contains(&port->tx_list, &tport->node)) {
            list_remove(&tport->node);
        }
    }

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
    ipc_port_init(port, req_pid);
    unwrap_err(p_attach(req_pid, owner, PORT_RECV | PORT_SEND));
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