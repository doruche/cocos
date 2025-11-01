/*
 * primary IPC machenism: ports
 */

#pragma once

#include "kernel/task/sched.h"
#include "libs/prelude.h"

// kernel global port object
typedef struct _ipc_port_t {
    port_t id;
    list_elem_t node; // node in global port list
    task_t* rx; // task who is receiving from the port. can be NULL
    list_t tx_list; // tasks who hold the send right of the port
    list_t tx_waitlist; // tasks waiting to send message to this port
} ipc_port_t;

// in-tcb port object
typedef struct _task_port_t {
    port_t id;
    port_flags_t privs; // priveledge flags
    list_elem_t node; // node in task's port list
} task_port_t;

void    ipc_init(void);

ipc_port_t* p_get(port_t id);


port_t  p_creat(port_t req_pid, task_t* owner);
isize   p_attach(port_t pid, task_t* owner, port_flags_t privs);
isize   p_transfer(
    port_t pid,
    task_t* dst,
    task_t* ori,
    port_flags_t flags   
);
isize   p_send(const msg_hdr_t* msg);
isize   p_recv(msg_hdr_t* msg);
isize   p_close(port_t pid, task_t* task);