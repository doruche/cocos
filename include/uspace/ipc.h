#pragma once

#include <libs/prelude.h>

result_t    p_creat(port_t req_pid, port_t* out);
result_t    p_close(port_t port);
result_t    p_send(const untyped_msg_t* msg);
result_t    p_notify(port_t port, notif_t notif);
result_t    p_recv(untyped_msg_t* msg, notif_t* notif);

result_t    p_call(
    untyped_msg_t* req,
    untyped_msg_t* resp,
    notif_t* notif
);

