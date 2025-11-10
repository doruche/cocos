#pragma once

#include <libs/prelude.h>

result_t    p_creat(port_t req_pid, port_t* out);
result_t    p_close(port_t port);
result_t    p_send(const untyped_msg_t* msg);
result_t    p_notify(port_t port, notif_t notif);
result_t    p_recv(untyped_msg_t* msg, notif_t* notif);

result_t    p_call(untyped_msg_t* msg, notif_t* notif);

result_t    pns_resolve(
    const char* name,
    port_t* out
);
result_t    pns_publish(
    const char* name,
    port_t port,
    u64* out_key
);
result_t    pns_unpublish(
    const char* name,
    u64 key
);

