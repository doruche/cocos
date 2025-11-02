#include "uspace/task.h"
#include "uspace/syscall.h"
#include "libs/elf.h"
#include "task.h"
#include "libs/prelude.h"
#include "uspace/servers/pm.h"

static port_t pm_port;

static void
pm_init(void) {
    trace("pm: initializing...");
    pm_port = sys_p_creat(PID_ANY);
    if (is_err(pm_port)) {
        panic("pm: failed to create pm port: %s",
            strerr((isize)pm_port));
    }
    trace("pm: created pm port %ld", pm_port);
    trace("pm: initialized.");
}

static void
handle_msg(pm_msg_t* msg) {
    port_t src_port = msg->header.remote;
    usize size = msg->header.size;
    msg_id_t msg_id = msg->header.id;
    printf("pm: handling message id %ld from port %ld, size=%ld\n",
        msg_id, src_port, size);

    switch (msg->header.id) {
        case PM_REQ_PING: {
            printf("pm: ping received with val=%ld\n",
                msg->body.ping.val);
            break;
        }
        default: {
            printf("pm: unknown message id %ld received\n",
                msg->header.id);
            break;
        }
    }
}

isize
main(void) {
    pm_init();

    extern u8 __app_elf[];
    tid_t test_procs[3];
    char namebuf[32] = "test_proc_0";
    for (usize i = 0; i < 3; i++) {
        // "test_proc_{i}"
        namebuf[10] = '0' + (char)i;
        namebuf[11] = '\0';
        tid_t tid = unwrap_err(hot_spawn(
            namebuf,
            __app_elf
        ));
        test_procs[i] = tid;
        unwrap_err(sys_p_transfer(
            pm_port,
            tid,
            PORT_SEND
        ));
    }

    // receiver no need to set other fields
    pm_msg_t msg;
    msg.header.local = pm_port;
    notifications_t notif;
    notifications_t mask = 0;


    loop {
        isize ret = sys_p_recv(
            (msg_hdr_t*)&msg,
            &notif,
            mask
        );
        if (is_err(ret)) {
            printf("pm: failed to receive message: %s\n",
                strerr(ret));
        } else if (notif != 0) {
            printf("pm: received notification: %lx\n",
                notif);
        } else {
            handle_msg(&msg);
        }
    }

    return 0;
}