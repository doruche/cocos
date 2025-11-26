#include "name.h"
#include <libs/prelude.h>
#include <libs/path.h>
#include <uspace/ipc.h>

static void
ns_init(void) {
    unwrap_err(tns_publish("ns"));
}

result_t
main(void) {
    ns_init();

    pr_info("ns server started.");

    loop {
        msg_t req = {0};
        result_t ret = ipc_recv(IPC_OPEN, &req);
        if (is_err(ret)) {
            pr_warn("ns: ipc_recv failed: %d", ret);
            continue;
        }
        msg_t resp = {0};
        switch (req.type) {
            case MSG_NOTIF: {
                if (req.notifs & NOTIF_ASYNC_PENDING) {
                    unwrap_err(async_recv(TID_PM, &req));
                    assert_eq(req.type, MSG_PM);
                    assert_eq(req.pm.type, PM_PROC_EXIT);
                    pr_info("ns: received process exit notif for pid %ld",
                        req.pm.proc_exit.pid);
                    s_ns_cleanup(req.pm.proc_exit.pid);
                }
                break;
            }
            case MSG_NS: {
                req.type = MSG_NS;
                switch (req.ns.type) {
                    case NS_MOUNT: {
                        if (!path_is_absolute(req.ns.mount.path)) {
                            pr_warn("ns: mount path must be absolute: %s",
                                req.ns.mount.path);
                            rpc_reply_result(req.src, -ERR_INVAL);
                            break;
                        }
                        ret = proc_watch(req.ns.mount.fs);
                        if (is_err(ret)) {
                            pr_warn("ns: failed to watch fs pid %ld: %s",
                                req.ns.mount.fs, strerr(ret));
                            rpc_reply_result(req.src, ret);
                            break;
                        }
                        ret = s_ns_mount(
                            req.ns.mount.path,
                            req.ns.mount.fs
                        );
                        if (is_err(ret)) {
                            pr_warn("ns: mount failed for %s: %s",
                                req.ns.mount.path, strerr(ret));
                        }
                        rpc_reply_result(req.src, ret);
                        break;
                    }
                    case NS_UMOUNT: {
                        if (!path_is_absolute(req.ns.umount.path)) {
                            pr_warn("ns: umount path must be absolute: %s",
                                req.ns.umount.path);
                            rpc_reply_result(req.src, -ERR_INVAL);
                            break;
                        }
                        ret = s_ns_umount(req.ns.umount.path);
                        if (is_err(ret)) {
                            pr_warn("ns: umount failed for path %s: %s",
                                req.ns.umount.path, strerr(ret));
                        }
                        rpc_reply_result(req.src, ret);
                        break;
                    }
                    case NS_RESOLVE: {
                        if (!path_is_absolute(req.ns.resolve.path)) {
                            pr_warn("ns: resolve path must be absolute: %s",
                                req.ns.resolve.path);
                            rpc_reply_result(req.src, -ERR_INVAL);
                            break;
                        }
                        pid_t fs = 0;
                        char rpath[PATH_MAX_LEN] = {0};
                        ret = s_ns_resolve(
                            req.ns.resolve.path,
                            &fs,
                            rpath
                        );
                        if (is_err(ret)) {
                            pr_warn("ns: resolve failed for path %s: %s",
                                req.ns.resolve.path, strerr(ret));
                            rpc_reply_result(req.src, ret);
                            break;
                        }
                        resp.ns.type = NS_RESOLVE_RESP;
                        resp.ns.resolve_resp.fs = fs;
                        strncpy(
                            resp.ns.resolve_resp.rpath,
                            rpath,
                            PATH_MAX_LEN
                        );
                        rpc_reply(req.src, &resp);
                        break;
                    }
                    default: {
                        pr_warn("ns: unknown ns message type %d from tid %ld",
                            req.ns.type, req.src);
                        break;
                    }
                }
                break;
            }
            default: {
                pr_warn("ns: unknown message type %ld from tid %ld",
                    req.type, req.src);
                break;
            }
        }
    }

    panic("ns server exited unexpectedly.");
}