#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/servers/echo.h>
#include <uspace/task.h>

result_t
main(void) {
    unwrap_err(pns_publish("echo"));

    pr_info("echo server started.");

    loop {
        msg_t msg = {0};
        result_t ret = ipc_recv(IPC_OPEN, &msg);
        if (is_err(ret)) {
            pr_warn("echo: ipc_recv failed: %s",
                strerr(ret));
            continue;
        }
        if (msg.type != MSG_ECHO) {
            pr_warn("echo: received unknown msg type %ld from %ld",
                msg.type, msg.src);
            continue;
        }
        
        msg_t resp = {0};
        resp.type = MSG_ECHO;
        switch (msg.echo.type) {
            case ECHO_ECHO: {
                msg.echo.echo.data[
                    msg.echo.echo.len - 1
                ] = '\0';
                pr_trace("echo: received echo msg from %ld: '%s'",
                    msg.src,
                    msg.echo.echo.data);
                resp.echo.type = ECHO_ECHO_RESP;
                strncpy(
                    resp.echo.echo_resp.data,
                    msg.echo.echo.data,
                    msg.echo.echo.len
                );
                resp.echo.echo_resp.len = msg.echo.echo.len;
                rpc_reply(msg.src, &resp);
                break;
            }
            default: {
                pr_warn("echo: received unknown echo msg type %ld from %ld",
                    msg.echo.type, msg.src);
                break;
            }
        }
    }

    return OK;
}