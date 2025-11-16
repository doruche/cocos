#pragma once

#include <libs/prelude.h>

/* One-way communication primitives provided by kernel */
result_t    p_creat(port_t req_pid, port_t* out);
result_t    p_close(port_t port);
result_t    p_send(port_t remote, const untyped_msg_t* msg);
result_t    p_notify(port_t port, notif_t notif);
result_t    p_recv(port_t local, untyped_msg_t* msg, notif_t* notif);

/* RPC methods encapsulated by user library */

#define RPC_MSG_SIZE (MSG_SIZE - 8)

typedef struct _rpc_packet_t {
    port_t reply_port;
    u8 payload[RPC_MSG_SIZE];
} rpc_packet_t;
static_assert(sizeof(rpc_packet_t) == MSG_SIZE);

/*
 * note that the first 8 bytes of MSG_SIZE are reserved for the
 * request/response size, so the actual size of the message
 * cannot be greater than MSG_SIZE - 8.
 *
 * The following void* type must be a pointer to a struct
 * whose size is equal to RPC_MSG_SIZE.
 * All servers should define their message structs accordingly,
 * for simplicity.
 */
result_t    rpc_call(
    port_t remote,
    const void* req,
    void* resp_buf,
    notif_t* notif_buf
);
result_t    rpc_recv(
    port_t local,
    void* req_buf,
    port_t* remote,
    notif_t* notif_buf
);
result_t    rpc_reply(
    port_t remote,
    const void* resp
);
