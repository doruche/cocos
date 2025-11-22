#pragma once

#include <libs/prelude.h>
#include <libs/list.h>

/* One-way communication primitives provided by kernel */
result_t ipc_send(tid_t send_to, const msg_t *msg);
result_t ipc_send_nonblock(tid_t send_to, const msg_t *msg);
result_t ipc_recv(tid_t recv_from, msg_t *msg);
result_t ipc_notify(tid_t dst, notif_t notif);

/* RPC methods encapsulated by user library */
result_t rpc_call(tid_t remote, msg_t *msg);
result_t rpc_reply(tid_t client, const msg_t *msg);
result_t rpc_reply_result(tid_t client, result_t res);
result_t rpc_recv(tid_t remote, msg_t *msg); /* this may encapsulate async_recv? */

/* user-level asynchronous IPC */
typedef struct _async_msg_t {
    tid_t send_to;
    msg_t msg;
    list_elem_t node; /* node in message queue */
} async_msg_t;
result_t async_send(tid_t send_to, const msg_t *msg);
result_t async_recv(tid_t recv_from, msg_t *msg);
result_t async_flush(tid_t send_to);

/*
 * TNS - Task Name System
 * In this simple kernel, it is implemented
 * directly inside the process manager server
 * for simplicity.
 * The reason we put these declarations here
 * is that TNS is a fundamental IPC-based
 * service that most user programs would use.
 */
result_t tns_resolve(const char *name, tid_t *out);
result_t tns_publish(const char *name);
result_t tns_unpublish(const char *name);
