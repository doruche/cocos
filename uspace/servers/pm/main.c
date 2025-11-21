#include "task.h"
#include "bfs.h"
#include "tns.h"
#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/syscall.h>
#include <uspace/servers/pm.h>

static void
spawn_tasks(const char* init_tasks[]) {
    for (usize i = 0; init_tasks[i] != NULL; i++) {
        const char* name = init_tasks[i];
        const bfs_inode_t* inode = unwrap_null(bfs_lookup(name));
        const u8* elf = bfs_read_inplace(inode);
        tid_t tid;
        unwrap_err(proc_spawn(
            name,
            elf,
            (const cmdline_t*)&(cmdline_t){
                .argc = 1,
                .argv = { (char*)name, NULL},
            },
            &tid
        ));
        pr_trace("pm: spawned init task '%s' (tid %ld)",
            name, tid);
    }
}

static void
spawn_init_tasks(void) {
    const char* init_servers[] = INIT_SERVERS;
    const char* init_apps[] = INIT_APPS;

    pr_info("pm: spawning init servers...");
    spawn_tasks(init_servers);
    pr_info("pm: spawning init apps...");
    spawn_tasks(init_apps);    
    pr_info("pm: all init tasks spawned.");
}

static void
pm_init(void) {
    /* self-map guard page */
    extern u8 __ustack_bottom[];
    unwrap_err(sys_as_map(
        unwrap_err(sys_as_get(TID_PM)),
        PA2PN((uaddr_t)__ustack_bottom - PAGE_SIZE),
        0,
        1,
        VM_READ | VM_WRITE | VM_FAKE
    ));

    bfs_probe();
    tns_init();
    spawn_init_tasks();
}

result_t
main(void) {
    pm_init();

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
                        pr_info("pm: task exited: tid=%ld exit_code=%ld %s",
                            ztask.tid, ztask.exit_code, strerr(ztask.exit_code));
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
                        resp.pm.type = PM_RESOLVE_NAME_RESP;
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
                        vpn_t vpn;
                        resp.pm.type = PM_MAP_RESP;
                        switch (msg.pm.map.type) {
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
                                rpc_reply_result(msg.src, -ERR_UNKNOWN_REQ);
                                break;
                            }
                        }
                        break;
                    }
                    case PM_SPAWN: {
                        tid_t proc_tid;
                        cmdline_t cmdline = {0};
                        cmd_parse_inplace(
                            msg.pm.spawn.cmdline,
                            &cmdline
                        );
                        /* currently, only support spawning from bfs */
                        const bfs_inode_t* inode = bfs_lookup(cmdline.argv[0]);
                        if (inode == NULL) {
                            pr_warn("pm: bfs_lookup failed for spawn cmd '%s' from %ld",
                                cmdline.argv[0], msg.src);
                            rpc_reply_result(msg.src, -ERR_NOENT);
                            break;
                        }
                        const u8* elf = bfs_read_inplace(inode);
                        ret = proc_spawn(
                            cmdline.argv[0],
                            elf,
                            (const cmdline_t*)&cmdline,
                            &proc_tid
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: proc_spawn failed for cmd '%s' from %ld: %s",
                                cmdline.argv[0], msg.src, strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.pm.type = PM_SPAWN_RESP;
                        resp.pm.spawn_resp.proc_tid = proc_tid;
                        rpc_reply(msg.src, &resp);
                        pr_info("pm: spawned process '%s' (tid %ld) for %ld",
                            cmdline.argv[0], proc_tid, msg.src);
                        break;
                    }
                    default: {
                        pr_warn("pm: received unknown pm msg type %ld from %ld",
                            msg.pm.type, msg.src);
                        rpc_reply_result(msg.src, -ERR_UNKNOWN_REQ);
                        break;
                    }
                }
                break;
            }
            default: {
                pr_warn("pm: received unknown msg type %ld from %ld",
                    msg.type, msg.src);
                rpc_reply_result(msg.src, -ERR_UNKNOWN_REQ);
                break;
            }
        }
    }

    panic("pm: pm should not exit main loop");
}