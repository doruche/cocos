/*
 * primary IPC machenism: ports
 */

#pragma once

#include <libs/prelude.h>
#include <kernel/task/sched.h>

/* kernel global port object */
typedef struct _ipc_port_t {
    port_t id;
    list_elem_t node; /* node in global port list */
    struct {
        task_t* task; /* task who created this port */
        bool is_receiving;
    } rx;
    list_t wtx; /* waiting tasks */
} ipc_port_t;

/* notification object in task's notif_list */
typedef struct _knotif_t {
    notif_t notif;
    list_elem_t node; /* node in task's notif list */
} knotif_t;

void    ipc_init(void);

result_t     p_get(port_t id, ipc_port_t** out);

result_t   p_creat(port_t req_pid, task_t* owner, port_t* out);
result_t   p_send(port_t remote, const untyped_msg_t* msg);
result_t   p_notify(port_t pid, notif_t notif);
result_t   k_notify(task_t* task, notif_t notif);
result_t   p_recv(
    port_t local,
    untyped_msg_t* msg, 
    notif_t* notif
);
result_t   p_close(port_t pid, task_t* task);

void       task_ipc_cleanup(task_t* task);

void       ipc_port_dump(void);
