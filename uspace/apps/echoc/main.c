#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/syscall.h>


result_t
main(void) {
    tid_t remote;
    while (is_err(pns_resolve("echo", &remote))) {
        sys_task_yield();
    }
    printf("echoc: resolved 'echo' server at pid %ld\n", remote);

    msg_t msg = {0};
    msg.type = MSG_ECHO;
    msg.echo.type = ECHO_ECHO;
    strcpy(msg.echo.echo.data, "Hello, Echo Server!");
    msg.echo.echo.len = strlen(msg.echo.echo.data) + 1;
    result_t ret = rpc_call(remote, &msg);
    if (is_err(ret)) {
        pr_warn("echoc: rpc_call to echo server failed: %s",
            strerr(ret));
    } else {
        printf("echoc: received echo response: '%s'\n",
            msg.echo.echo_resp.data);
    }

    return OK;
}