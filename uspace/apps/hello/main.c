#include "libs/prelude.h"
#include "uspace/syscall.h"
#include "uspace/servers/pm.h"

static port_t pm_port = 1;

static isize
ping_pm(usize val) {
    pm_msg_t req;
    memset(&req, 0, sizeof(req));
    req.header.local = PID_INVALID; // one-way message.
    req.header.remote = pm_port;
    req.header.id = PM_REQ_PING;
    req.body.ping.val = val;
    isize ret = sys_p_send((msg_hdr_t*)&req);
    return ret;
}

isize
main(int argc, char* argv[]) {
    printf("hello from hello app!\n");
    
    for (usize i = 0; i < 2; i++) {
        isize ret = ping_pm(i * i);
        if (is_err(ret)) {
            printf("hello: failed to ping pm: %s\n",
                strerr(ret));
        } else {
            printf("hello: pinged pm with val=%ld\n",
                i * i);
        }
    }

    // try to send to dead port
    isize ret = ping_pm(42);
    assert(is_err(ret));
    printf("hello: ping to dead pm port failed as expected: %s\n",
        strerr(ret));

    sys_p_close(pm_port);
    loop {}

    return 0;
}