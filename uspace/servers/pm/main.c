#include "task.h"
#include "bfs.h"
#include "pns.h"
#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/syscall.h>
#include <uspace/servers/pm.h>
#include <uspace/servers/pns.h>

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

        /* set up initial IPC ports */
        // unwrap_err(sys_p_transfer(PID_PM, tid, PORT_SEND));
        unwrap_err(sys_p_transfer(PID_PNS, tid, PORT_SEND));

        trace("pm: spawned init task '%s' (tid %ld)",
            inode->name, tid);
    }

    trace("pm: init tasks spawned.");
}

static result_t
pm_handle_msg(pm_msg_t* msg) {
    switch (msg->header.id) {
        case PM_PING:
            trace("pm: received ping request");
            msg->body.ping_resp.val = msg->body.ping.val;
            msg->header.remote = msg->header.aux_xfer.port;
            msg->header.aux_xfer.port = PID_INVALID;
            msg->header.aux_xfer.flags = 0;
            result_t ret = p_send((untyped_msg_t*)msg);
            if (is_err(ret)) {
                warn("pm: failed to send ping response: %s", strerr(ret));
                return ret;
            }
            p_close(msg->header.remote);
            trace("pm: sent ping response");
            return OK;
        default:
            warn("pm: received unknown pm message id %ld",
                msg->header.id);
            return -ERR_NOENT;
    }
}

static result_t
msg_dispatch(untyped_msg_t* msg) {
    switch (msg->header.local) {
        case PID_PM: return pm_handle_msg((pm_msg_t*)msg);
        case PID_PNS: return pns_handle_msg((pns_msg_t*)msg);
        default:
            warn("pm: received message for unknown port %ld",
                msg->header.local);
            return -ERR_NOENT;
    }
}

static result_t
handle_notif(notif_t* notif) {
    switch (notif->type) {
        case NOTIF_TASK_EXIT:
            trace("pm: task %ld exited with code %ld",
                notif->payload.task_exited.tid,
                notif->payload.task_exited.exit_code);
            /* TODO: cleanup resources */
            return OK;
        default:
            warn("pm: received unknown notification type %ld",
                notif->type);
            return -ERR_NOENT;
    }
}

result_t __noreturn
main(void) {
    bfs_probe();
    pns_init();

    spawn_init_tasks();

    loop {
        untyped_msg_t msg = {0};
        msg.header.local = PID_ANY;
        notif_t notif = {0};
        result_t ret = p_recv(&msg, &notif);
        if (is_err(ret)) {
            warn("pm: sys_p_recv failed: %s", strerr(ret));
            continue;
        } else if (notif.type != 0) {
            ret = handle_notif(&notif);
            if (is_err(ret)) {
                warn("pm: notification handling failed: %s", strerr(ret));
            }
        } else {
            ret = msg_dispatch(&msg);
            if (is_err(ret)) {
                warn("pm: message dispatch failed: %s", strerr(ret));
            }
        }
    }

    panic("pm: pm should not exit main loop");
}