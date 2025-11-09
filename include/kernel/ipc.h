/*
 * primary IPC machenism: ports
 */

#pragma once

#include <libs/prelude.h>
#include <kernel/task/sched.h>

// kernel global port object
typedef struct _ipc_port_t {
    port_t id;
    // whether rx closed the port
    bool dead;
    // tx reference count. if zero and rx closed, free the port.
    usize tx_rc;
    list_elem_t node; // node in global port list
    struct {
        task_t* task;
        bool is_receiving;
    } rx;
    list_t wtx; /* waiting tasks */
} ipc_port_t;

// in-tcb port object
typedef struct _task_port_t {
    port_t id;
    port_flags_t privs; // priveledge flags
    list_elem_t node; // node in task's port list
} task_port_t;

// notification object in task's notif_list
typedef struct _knotif_t {
    notif_t notif;
    list_elem_t node; // node in task's notif list
} knotif_t;

void    ipc_init(void);

result_t     p_get(port_t id, ipc_port_t** out);
result_t     tp_get(task_t* task, port_t pid, task_port_t** out);
result_t     tp_attach(port_t pid, task_t* owner, port_flags_t privs);

result_t   p_creat(port_t req_pid, task_t* owner, port_t* out);
result_t   p_transfer(
    port_t pid,
    task_t* dst,
    task_t* ori,
    port_flags_t flags   
);
result_t   p_send(const msg_hdr_t* msg);
result_t   p_notify(port_t pid, notif_t notif);
result_t   p_knotify(port_t pid, notif_t notif);
result_t   p_recv(msg_hdr_t* msg, notif_t* notif);
result_t   p_close(port_t pid, task_t* task);

void       task_ipc_cleanup(task_t* task);
