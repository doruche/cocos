#include <libs/prelude.h>
#include <uspace/rpc.h>
#include <uspace/syscall.h>
#include <uspace/servers/pns.h>

result_t
p_creat(port_t req_pid, port_t* out) {
    result_t ret = sys_p_creat(req_pid);
    if (!is_err(ret)) {
        *out = (port_t)ret;
    }
    return ret;
}

result_t
p_close(port_t port) {
    return sys_p_close(port);
}

result_t
p_send(
    port_t remote,
    const untyped_msg_t* msg
) {
    return sys_p_send(remote, msg);
}

result_t
p_notify(port_t port, notif_t notif) {
    return sys_p_notify(port, &notif);
}

result_t
p_recv(
    port_t local,
    untyped_msg_t* msg,
    notif_t* notif
) {
    return sys_p_recv(local, msg, notif);
}

result_t
rpc_call(
    port_t remote,
    const void* req,
    void* resp_buf,
    notif_t* notif_buf
) {
    result_t ret;

    port_t reply_port = PID_INVALID;
    ret = p_creat(PID_ANY, &reply_port);
    if (is_err(ret)) {
        goto out;
    }

    rpc_packet_t packet = {0};
    packet.reply_port = reply_port;
    memcpy(packet.payload, req, RPC_MSG_SIZE);
    ret = p_send(remote, (untyped_msg_t*)&packet);
    if (is_err(ret)) {
        goto out;
    }
    packet = (rpc_packet_t){0};
    ret = p_recv(reply_port, (untyped_msg_t*)&packet, notif_buf);
    if (is_err(ret)) {
        goto out;
    }
    memcpy(resp_buf, packet.payload, RPC_MSG_SIZE);

out:
    if (reply_port != PID_INVALID) {
        unwrap_err(p_close(reply_port));
    }
    return ret;
}

result_t
rpc_recv(
    port_t local,
    void* req_buf,
    port_t* remote,
    notif_t* notif_buf
) {
    result_t ret;
    rpc_packet_t packet = {0};
    ret = p_recv(local, (untyped_msg_t*)&packet, notif_buf);
    if (is_err(ret)) {
        goto out;
    }

    memcpy(req_buf, packet.payload, RPC_MSG_SIZE);
    *remote = packet.reply_port;
    ret = OK;

out:
    return ret;
}

result_t
rpc_reply(
    port_t remote,
    const void* resp
) {
    rpc_packet_t packet = {0};
    packet.reply_port = PID_INVALID;
    memcpy(packet.payload, resp, RPC_MSG_SIZE);
    return p_send(remote, (untyped_msg_t*)&packet);
}
