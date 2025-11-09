#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/syscall.h>

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
p_send(const untyped_msg_t* msg) {
    return sys_p_send(msg);
}

result_t
p_notify(port_t port, notif_t notif) {
    return sys_p_notify(port, &notif);
}

result_t
p_recv(untyped_msg_t* msg, notif_t* notif) {
    return sys_p_recv(msg, notif);
}

result_t
p_call(
    untyped_msg_t* req,
    untyped_msg_t* resp,
    notif_t* notif
) {
    assert_eq(req->header.aux_xfer.port, PID_INVALID);
    assert_eq(resp->header.local, PID_INVALID);

    result_t ret = OK;
    port_t aux_port = 0;

    ret = p_creat(PID_ANY, &aux_port);
    if (is_err(ret)) {
        goto done;
    }
    req->header.aux_xfer.port = aux_port;
    req->header.aux_xfer.flags = PORT_SEND | PORT_TRANSFER_DISCARD;
    ret = p_send(req);
    if (is_err(ret)) {
        goto done;
    }
    resp->header.local = aux_port;
    ret = p_recv(resp, notif);
    if (is_err(ret)) {
        goto done;
    }

done:
    if (aux_port != 0) {
        unwrap_err(p_close(aux_port));
    }
    return ret;
}
