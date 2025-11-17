/*
 * primary IPC machenism: ports
 */

#pragma once

#include <libs/prelude.h>
#include <kernel/task/sched.h>

result_t ipc(
    task_t* send_to,
    tid_t recv_from,
    msg_t* msg,
    ipc_flags_t flags
);

result_t notify(task_t* dst, notif_t notifs);
