/*
 * primary IPC machenism: ports
 */

#pragma once

#include "kernel/task/sched.h"
#include "libs/prelude.h"

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
    struct {
        list_t tasks;
        list_t waiting_tasks;
    } tx;
} ipc_port_t;

// in-tcb port object
typedef struct _task_port_t {
    port_t id;
    port_flags_t privs; // priveledge flags
    list_elem_t node; // node in task's port list
} task_port_t;

void    ipc_init(void);

ipc_port_t*     p_get(port_t id);
task_port_t*    tp_get(task_t* task, port_t pid);

port_t  p_creat(port_t req_pid, task_t* owner);
isize   p_transfer(
    port_t pid,
    task_t* dst,
    task_t* ori,
    port_flags_t flags   
);
isize   p_send(const msg_hdr_t* msg);
isize   p_notify(port_t pid, notifications_t notif);
isize   p_recv(
    msg_hdr_t* msg, 
    notifications_t* notif,
    notifications_t mask
);
isize   p_close(port_t pid, task_t* task);
