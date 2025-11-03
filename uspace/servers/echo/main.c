#include "libs/prelude.h"
#include "uspace/syscall.h"
#include "uspace/servers/echo.h"

static port_t port = 2; // hardcoded for debugging

isize
main(void) {
    echo_msg_t msg;
    msg.header.local = port;
    notifications_t notif;
    
    usize time = 7;

    loop {
        isize ret = sys_p_recv(
            (msg_hdr_t*)&msg,
            &notif,
            NOTIF_MASK_ALL
        );
        if (is_err(ret)) {
            printf("echo: sys_p_recv failed: %s\n",
                strerr(ret));
        } else if (notif != 0) {
            printf("echo: received notification: 0x%lx\n",
                notif);
        } else {
            static char buf[ECHO_MSG_MAX_LEN];
            assert_eq(msg.header.id, ECHO_REQ_ECHO);
            memcpy(
                buf,
                msg.body.echo.data,
                msg.body.echo.len
            );
            buf[msg.body.echo.len] = '\0';
            printf("echo: received echo request: \"%s\"\n",
                buf);
        }
        sys_task_yield();
        time--;
        if (time == 0) {
            break;
        }
    }
    sys_p_close(port);
    loop {}

    return 0;
}