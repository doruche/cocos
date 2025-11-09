#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/servers/pns.h>
#include <uspace/servers/echo.h>

static port_t echo_port;

result_t
main(void) {
    unwrap_err(p_creat(PID_ANY, &echo_port));
    pns_msg_t pns_msg = {0};
    pns_msg.header.remote = PID_PNS;
    pns_msg.header.id = PNS_REQ_PUBLISH;
    pns_msg.header.aux_xfer.port = echo_port;
    pns_msg.header.aux_xfer.flags = PORT_SEND;
    strcpy(pns_msg.body.publish.name, "echo");
    result_t ret = p_call(
        (untyped_msg_t*)&pns_msg,
        (untyped_msg_t*)&pns_msg,
        NULL
    );
    if (is_err(ret)) {
        panic("echo: failed to publish echo service: %s", strerr(ret));
    }
    if (!pns_msg.body.publish_resp.success) {
        panic("echo: pns refused to publish echo service");
    }

    printf("echo: listening on port %ld\n", echo_port);

    loop {
        echo_msg_t msg = {0};
        notif_t notif = {0};
        result_t ret = p_recv((untyped_msg_t*)&msg, &notif);
        if (is_err(ret)) {
            warn("echo: p_recv failed: %s", strerr(ret));
            continue;
        } else if (notif.type != 0) {
            warn("echo: received unexpected notification type %ld", notif.type);
            continue;
        } else {
            switch (msg.header.id) {
                case ECHO_REQ_ECHO:
                    char buf[ECHO_MSG_MAX_LEN] = {0};
                    usize len = min(msg.body.echo.len, ECHO_MSG_MAX_LEN - 1);
                    memcpy(buf, msg.body.echo.data, len);
                    printf("echo: received message: '%s'\n", buf);
                    break;
                default:
                    printf("echo: received unknown message id %ld\n", msg.header.id);
            }
        }
        
    }

    return OK;
}