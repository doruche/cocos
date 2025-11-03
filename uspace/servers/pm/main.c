#include "uspace/syscall.h"
#include "task.h"
#include "bfs.h"
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
    bfs_probe();
    trace("pm: created pm port %ld", pm_port);
    trace("pm: initialized.");
}

static void
handle_msg(pm_msg_t* msg) {
    port_t src_port = msg->header.remote;
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
        tid_t tid = unwrap_err(hot_spawn(inode->name, elf, false));
        unwrap_err(sys_p_transfer(pm_port, tid, PORT_SEND));
        trace("pm: spawned init task '%s' (tid %ld)",
            inode->name, tid);
        unwrap_err(sys_task_resume(tid));
    }

    trace("pm: init tasks spawned.");
}

isize
main(void) {
    pm_init();

    spawn_init_tasks();

    pm_msg_t msg;
    msg.header.local = pm_port;
    notifications_t notif;
    notifications_t mask = NOTIF_MASK_ALL;
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
        sys_task_yield();
    }

    sys_p_close(pm_port);

    loop {}

    return 0;
}