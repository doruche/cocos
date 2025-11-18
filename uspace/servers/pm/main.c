#include "task.h"
#include "bfs.h"
#include "tns.h"
#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/syscall.h>
#include <uspace/servers/pm.h>

static void
spawn_init_tasks(void) {
    pr_trace("pm: spawning init tasks...");

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

        pr_trace("pm: spawned init task '%s' (tid %ld)",
            inode->name, tid);
    }

    pr_trace("pm: init tasks spawned.");
}

result_t
main(void) {
    bfs_probe();
    tns_init();

    spawn_init_tasks();    

    pr_info("pm server started.");

    loop {
        msg_t msg = {0};
        result_t ret = ipc_recv(IPC_OPEN, &msg);
        if(is_err(ret)) {
            pr_warn("pm: ipc_recv failed: %s",
                strerr(ret));
            continue;
        }
        msg_t resp = {0};

        switch (msg.type) {
            case MSG_NOTIF: {
                pr_trace("pm: received notif from %ld: 0x%lx",
                    msg.src, msg.notifs);
                if (msg.notifs & NOTIF_TASK_EXIT) {
                    zombie_task_t ztask;
                    while (!is_err(sys_task_getzombie(&ztask))) {
                        pr_info("pm: task exited: tid=%ld exit_code=%ld",
                            ztask.tid, ztask.exit_code);
                        unwrap_err(task_free(ztask.tid));
                        unwrap_err(sys_task_destroy(ztask.tid));
                    }
                }
                break;
            }
            case MSG_EXCEPT: {
                if (msg.src != TID_KERNEL) {
                    pr_warn("pm: received except msg from non-kernel task %ld",
                        msg.src);
                    break;
                }
                pr_trace("pm: received except from %ld: type=%ld",
                    msg.src, msg.except.type);
                pr_warn("pm: unhandled exception message");
                break;
            }
            case MSG_PM: {
                pr_trace("pm: received pm msg from %ld: type=%ld",
                    msg.src, msg.pm.type);
                resp.type = MSG_PM;
                switch (msg.pm.type) {
                    case PM_PING: {
                        resp.pm.type = PM_PING_RESP;
                        resp.pm.ping_resp.val = msg.pm.ping.val;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case PM_RESOLVE_NAME: {
                        tid_t server_tid;
                        ret = tn_lookup(
                            msg.pm.resolve_name.name,
                            &server_tid
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: tns_lookup failed for name '%s': %s",
                                msg.pm.resolve_name.name,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.pm.resolve_name_resp.server_tid = server_tid;
                        pr_trace("pm: resolved service '%s' to %ld for %ld",
                            msg.pm.resolve_name.name,
                            server_tid,
                            msg.src);
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case PM_PUBLISH: {
                        ret = tn_insert(
                            msg.pm.publish.name,
                            msg.pm.publish.server_tid
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: tns_insert failed for name '%s': %s",
                                msg.pm.publish.name,
                                strerr(ret));
                        }
                        rpc_reply_result(msg.src, ret);
                        if (ret == OK) {
                            pr_info("pm: published service '%s' from %ld",
                                msg.pm.publish.name, msg.src);
                        }
                        break;
                    }
                    case PM_UNPUBLISH: {
                        tid_t server_tid;
                        ret = tn_lookup(
                            msg.pm.unpublish.name,
                            &server_tid
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: tns_lookup failed for name '%s': %s",
                                msg.pm.unpublish.name, strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        if (server_tid != msg.src) {
                            rpc_reply_result(msg.src, -ERR_PERM);
                            break;
                        }
                        unwrap_err(tn_remove(msg.pm.unpublish.name));
                        rpc_reply_result(msg.src, OK);
                        pr_info("pm: unpublished service '%s' from %ld",
                            msg.pm.unpublish.name, msg.src);
                        break;
                    }
                    case PM_MAP: {
                        switch (msg.pm.map.type) {
                            vpn_t vpn;
                            case PM_MAP_ANON: {
                                ret = vm_map_anon(
                                    msg.src,
                                    msg.pm.map.info.anon.npages,
                                    &vpn
                                );
                                if (is_err(ret)) {
                                    pr_warn("pm: vm_map_anon failed for tid %ld: %s",
                                        msg.src, strerr(ret));
                                    rpc_reply_result(msg.src, ret);
                                    break;
                                }
                                resp.pm.map_resp.vpn = vpn;
                                rpc_reply(msg.src, &resp);
                                break;
                            }
                            case PM_MAP_MMIO: {
                                ret = vm_map_mmio(
                                    msg.src,
                                    msg.pm.map.info.mmio.ppn,
                                    msg.pm.map.info.mmio.npages,
                                    &vpn
                                );
                                if (is_err(ret)) {
                                    pr_warn("pm: vm_map_mmio failed for tid %ld: %s",
                                        msg.src, strerr(ret));
                                    rpc_reply_result(msg.src, ret);
                                    break;
                                }
                                resp.pm.map_resp.vpn = vpn;
                                rpc_reply(msg.src, &resp);
                                break;
                            }
                            default: {
                                pr_warn("pm: unknown map type %ld from %ld",
                                    msg.pm.map.type, msg.src);
                                rpc_reply_result(msg.src, -ERR_INVAL);
                                break;
                            }
                        }
                        break;
                    }
                    default: {
                        pr_warn("pm: received unknown pm msg type %ld from %ld",
                            msg.pm.type, msg.src);
                        break;
                    }
                }
                break;
            }
            default: {
                pr_warn("pm: received unknown msg type %ld from %ld",
                    msg.type, msg.src);
                break;
            }
        }
    }

    panic("pm: pm should not exit main loop");
}