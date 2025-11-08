#include "task.h"
#include "bfs.h"
#include <libs/prelude.h>
#include <uspace/syscall.h>
#include <uspace/servers/pm.h>

static port_t pm_port;

static void
pm_init(void) {
    trace("pm: initializing...");
    pm_port = sys_p_creat(PID_ANY);
    if (is_err(pm_port)) {
        panic("pm: failed to create pm port: %s",
            strerr((isize)pm_port));
    }
    bfs_probe();
    trace("pm: created pm port %ld", pm_port);
    trace("pm: initialized.");
}

static void
handle_msg(pm_msg_t* msg) {
    port_t src_port = msg->header.local;
    msg_id_t msg_id = msg->header.id;
    printf("pm: handling message id %ld from port %ld\n",
        msg_id, src_port);
    
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


static void
spawn_init_tasks(void) {
    trace("pm: spawning init tasks...");

    usize i = 0;
    loop { 
        const bfs_inode_t* inode = bfs_inode(i++);
        if (inode == NULL) {
            break;
        }
        const u8* elf = bfs_read_inplace(inode);
        tid_t tid;
        result_t ret = proc_spawn(
            inode->name,
            elf,
            &tid
        );
        if (is_err(ret)) {
            panic("pm: failed to spawn init task '%s': %s",
                inode->name,
                strerr(ret));
        }
        trace("pm: spawned init task '%s' (tid %ld)",
            inode->name, tid);
    }

    trace("pm: init tasks spawned.");
}

isize
main(void) {
    pm_init();

    spawn_init_tasks();

    pm_msg_t msg;
    msg.header.local = PID_PM;
    notif_t notif = {0};
    
    loop {
        isize ret = sys_p_recv((msg_hdr_t*)&msg, &notif);
        if (is_err(ret)) {
            printf("pm: failed to receive message: %s\n",
                strerr(ret));
        } else if (notif.type != 0) {
            printf("pm: received notification of type %ld\n",
                notif.type);
            switch (notif.type) {
                case NOTIF_TASK_EXIT:
                    tid_t exited_tid = notif.payload.task_exited.tid;
                    result_t exit_code = notif.payload.task_exited.exit_code;
                    printf("pm: task %ld exited with code %ld\n", exited_tid, exit_code);
                    break;
                default:
                    printf("pm: unknown notification type %ld received\n",
                        notif.type);
                    break;
            }
            notif = (notif_t){0};
        } else {
            handle_msg(&msg);
        }
    }

    sys_p_close(pm_port);

    loop {}

    return 0;
}