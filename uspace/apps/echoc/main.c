#include "libs/prelude.h"
#include "uspace/syscall.h"
#include "uspace/servers/echo.h"

static port_t echo_port = 2; // hardcoded for debugging

isize
do_echo(const char* msg) {
    if (strlen(msg) >= ECHO_MSG_MAX_LEN) {
        printf("do_echo: message too long\n");
        return -ERR_INVAL;
    }
    echo_msg_t m;
    m.header.remote = echo_port;
    m.header.local = PID_INVALID; // one-way message
    m.header.id = ECHO_REQ_ECHO;
    m.body.echo.len = strlen(msg);
    strncpy(
        m.body.echo.data,
        msg,
        m.body.echo.len
    );
    isize ret = sys_p_send((msg_hdr_t*)&m);
    return ret;
}

isize
main(void) {
 
    char buf[128] = {0};
    strcpy(buf, "message_i from task t");
    usize counter = 0;
    tid_t tid = sys_task_gettid();
    buf[20] = '0' + (tid % 10);   

    loop {
        buf[8] = '0' + (counter++ % 10);
        
        isize ret = do_echo(buf);
        if (is_err(ret)) {
            printf("echoc: do_echo failed: %s\n",
                strerr(ret));
            if (ret == -ERR_ABORT) {
                printf("echoc: echo server closed port");
                break;
            }
        } else {
            printf("echoc: echoed message: \"%s\"\n",
                buf);
        }
    }

    assert(is_err(sys_p_close(1)));
    unwrap_err(sys_p_close(echo_port));

    loop {}
 
    return 0;
}