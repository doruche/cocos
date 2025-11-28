#include "proc.h"
#include "bfs.h"
#include "pns.h"
#include "ns.h"
#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/syscall.h>

static void
spawn_tasks(const char* init_tasks[]) {
    for (usize i = 0; init_tasks[i] != NULL; i++) {
        const char* name = init_tasks[i];
        const bfs_inode_t* inode = unwrap_null(bfs_lookup(name));
        const u8* elf = bfs_read_inplace(inode);
        tid_t pid;
        unwrap_err(s_proc_spawn(
            name,
            elf,
            (const cmdline_t*)&(cmdline_t){
                .argc = 1,
                .argv = { (char*)name, NULL},
            },
            s_ns_new(),
            &pid
        ));
        pr_trace("pm: spawned init task '%s' (pid %ld)",
            name, pid);
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
    pns_init();
    ns_init();
    task_init();
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
                    bool found = false;
                    while (!is_err(sys_task_getzombie(&ztask))) {
                        found = true;
                        pr_info("pm: process exited: tid=%ld exit_code=%ld %s",
                            ztask.tid, ztask.exit_code, strerr(ztask.exit_code));
                        unwrap_err(s_proc_exit(ztask.tid, ztask.exit_code));
                    }
                    if (!found) {
                        pr_warn("pm: received TASK_EXIT notif but no zombie task found\n"
                                "we may have already killed the task earlier.");
                    }
                }
                break;
            }
            case MSG_ASYNC_PULL: {
                ret = async_flush(msg.src);
                if (is_err(ret)) {
                    pr_warn("pm: async_flush failed for %ld: %s",
                        msg.src, strerr(ret));
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
                        tid_t server_pid;
                        ret = pn_lookup(
                            msg.pm.resolve_name.name,
                            &server_pid
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: pns_lookup failed for name '%s': %s",
                                msg.pm.resolve_name.name,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.pm.type = PM_RESOLVE_NAME_RESP;
                        resp.pm.resolve_name_resp.server_pid = server_pid;
                        pr_trace("pm: resolved service '%s' to %ld for %ld",
                            msg.pm.resolve_name.name,
                            server_pid,
                            msg.src);
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case PM_PUBLISH: {
                        ret = pn_insert(
                            msg.pm.publish.name,
                            msg.pm.publish.server_pid
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: pns_insert failed for name '%s': %s",
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
                        tid_t server_pid;
                        ret = pn_lookup(
                            msg.pm.unpublish.name,
                            &server_pid
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: pns_lookup failed for name '%s': %s",
                                msg.pm.unpublish.name, strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        if (server_pid != msg.src) {
                            rpc_reply_result(msg.src, -ERR_PERM);
                            break;
                        }
                        unwrap_err(pn_remove(msg.pm.unpublish.name));
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
                                ret = s_vm_map_anon(
                                    msg.src,
                                    msg.pm.map.info.anon.npages,
                                    &vpn
                                );
                                if (is_err(ret)) {
                                    pr_warn("pm: s_vm_map_anon failed for pid %ld: %s",
                                        msg.src, strerr(ret));
                                    rpc_reply_result(msg.src, ret);
                                    break;
                                }
                                resp.pm.map_resp.vpn = vpn;
                                rpc_reply(msg.src, &resp);
                                break;
                            }
                            case PM_MAP_MMIO: {
                                ret = s_vm_map_mmio(
                                    msg.src,
                                    msg.pm.map.info.mmio.ppn,
                                    msg.pm.map.info.mmio.npages,
                                    &vpn
                                );
                                if (is_err(ret)) {
                                    pr_warn("pm: s_vm_map_mmio failed for pid %ld: %s",
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
                    case PM_PROC_SPAWN: {
                        tid_t pid;
                        cmdline_t cmdline = {0};
                        cmd_parse_inplace(
                            msg.pm.proc_spawn.cmdline,
                            &cmdline
                        );
                        /* currently, only support spawning from bfs */
                        const bfs_inode_t* inode = bfs_lookup(
                            msg.pm.proc_spawn.path
                        );
                        if (inode == NULL) {
                            pr_warn("pm: bfs_lookup failed for spawn cmd '%s' from %ld",
                                msg.pm.proc_spawn.path, msg.src);
                            rpc_reply_result(msg.src, -ERR_NOT_FOUND);
                            break;
                        }
                        const u8* elf = bfs_read_inplace(inode);

                        struct name_space* ns = NULL;
                        if (msg.pm.proc_spawn.inherit_ns) {
                            struct process_t* spawner = NULL;
                            unwrap_err(s_proc_get(msg.src, &spawner));
                            ns = spawner->ns;
                        } else {
                            ns = s_ns_new();
                        }

                        ret = s_proc_spawn(
                            msg.pm.proc_spawn.path,
                            elf,
                            (const cmdline_t*)&cmdline,
                            ns,
                            &pid
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: s_proc_spawn failed for cmd '%s' from %ld: %s",
                                msg.pm.proc_spawn.path, msg.src, strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.pm.type = PM_PROC_SPAWN_RESP;
                        resp.pm.proc_spawn_resp.pid = pid;
                        rpc_reply(msg.src, &resp);
                        pr_info("pm: spawned process '%s' (pid %ld) for %ld",
                            msg.pm.proc_spawn.path, pid, msg.src);
                        break;
                    }
                    case PM_PROC_KILL: {
                        ret = s_proc_kill(msg.pm.proc_kill.pid);
                        if (is_err(ret)) {
                            pr_warn("pm: s_proc_kill failed for pid %ld by %ld: %s",
                                msg.pm.proc_kill.pid,
                                msg.src,
                                strerr(ret));
                        }
                        rpc_reply_result(msg.src, ret);
                        break;
                    }
                    case PM_PROC_PROBE: {
                        struct process_t* proc = NULL;
                        ret = s_proc_get(
                            msg.pm.proc_probe.pid,
                            &proc
                        );
                        /* 
                         * maybe proc already exited, or maybe it doesn't exist. 
                         * we don't care 
                         */
                        rpc_reply_result(msg.src, ret);
                        break;
                    }
                    case PM_PROC_WATCH: {
                        ret = s_proc_watch(
                            msg.src,
                            msg.pm.proc_watch.pid
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: s_proc_watch failed for pid %ld by %ld: %s",
                                msg.pm.proc_watch.pid,
                                msg.src,
                                strerr(ret));
                        }
                        rpc_reply_result(msg.src, ret);
                        break;
                    }
                    case PM_PROC_UNWATCH: {
                        ret = s_proc_unwatch(
                            msg.src,
                            msg.pm.proc_watch.pid
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: s_proc_unwatch failed for pid %ld by %ld: %s",
                                msg.pm.proc_unwatch.pid,
                                msg.src,
                                strerr(ret));
                        }
                        rpc_reply_result(msg.src, ret);
                        break;
                    }
                    case PM_NS_MOUNT: {
                        struct process_t* proc = NULL;
                        unwrap_err(s_proc_get(msg.src, &proc));
                        ret = s_ns_mount(
                            proc->ns,
                            msg.pm.mount.path,
                            msg.pm.mount.owner
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: s_ns_mount failed for path '%s' by %ld: %s",
                                msg.pm.mount.path,
                                msg.src,
                                strerr(ret));
                        }
                        rpc_reply_result(msg.src, ret);
                        break;
                    }
                    case PM_NS_UMOUNT: {
                        struct process_t* proc = NULL;
                        unwrap_err(s_proc_get(msg.src, &proc));
                        ret = s_ns_umount(
                            proc->ns,
                            msg.pm.umount.path
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: s_ns_umount failed for path '%s' by %ld: %s",
                                msg.pm.umount.path,
                                msg.src,
                                strerr(ret));
                        }
                        rpc_reply_result(msg.src, ret);
                        break;
                    }
                    case PM_NS_RESOLVE: {
                        struct process_t* proc = NULL;
                        unwrap_err(s_proc_get(msg.src, &proc));
                        tid_t owner;
                        char rpath[PATH_MAX_LEN];
                        ret = s_ns_resolve(
                            proc->ns,
                            msg.pm.resolve.path,
                            &owner,
                            rpath
                        );
                        if (is_err(ret)) {
                            pr_warn("pm: s_ns_resolve failed for path '%s' by %ld: %s",
                                msg.pm.resolve.path,
                                msg.src,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.pm.type = PM_NS_RESOLVE_RESP;
                        resp.pm.resolve_resp.owner = owner;
                        strncpy(
                            resp.pm.resolve_resp.rpath,
                            rpath,
                            PATH_MAX_LEN
                        );
                        rpc_reply(msg.src, &resp);
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