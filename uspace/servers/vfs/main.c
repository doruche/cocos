#include "filesystem.h"
#include "procfs.h"
#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/task.h>

static void
vfs_init(void) {
    unwrap_err(tns_publish("vfs"));

    pr_info("vfs server started.");
}

result_t __noreturn
main(void) {
    vfs_init();

    loop {        
        msg_t msg = {0};
        result_t ret = ipc_recv(IPC_OPEN, &msg);
        if (is_err(ret)) {
            pr_warn("vfs: ipc_recv failed: %s",
                strerr(ret));
            continue;
        }
        msg_t resp = {0};

        switch (msg.type) {
            case MSG_NOTIF: {
                pr_trace("vfs: received notif from %ld: 0x%lx",
                    msg.src, msg.notifs);
                if (msg.notifs & NOTIF_ASYNC_PENDING) {
                    ret = async_recv(TID_PM, &msg);
                    assert_eq(msg.type, MSG_PM);
                    assert_eq(msg.pm.type, PM_PROC_EXIT);
                    
                    /* for file system server process */
                    vfs_umount(msg.pm.proc_exit.pid);
                    pr_info("vfs: unmounted fs %ld",
                        msg.pm.proc_exit.pid);
                
                    /* for common clients who open files */
                    proc_exit(msg.pm.proc_exit.pid);
                }
                break;
            }
            case MSG_VFS: {
                pr_trace("vfs: received vfs msg from %ld: type=%ld",
                    msg.src, msg.vfs.type);
                resp.type = MSG_VFS;
                switch (msg.vfs.type) {
                    case VFS_MOUNT: {
                        ret = vfs_mount(
                            msg.src,
                            msg.vfs.mount.path
                        );
                        if (is_err(ret)) {
                            pr_warn("vfs: vfs_mount failed for tid %ld: %s",
                                msg.src, strerr(ret));
                        } else {
                            pr_info("vfs: mounted fs %ld at '%s'",
                                msg.src,
                                msg.vfs.mount.path);
                        }
                        rpc_reply_result(msg.src, ret);
                        break;
                    }
                    case VFS_OPEN: {
                        u64 fd = 0;
                        ret = proc_open(
                            msg.src,
                            msg.vfs.open.path,
                            msg.vfs.open.flags,
                            &fd
                        );
                        if (is_err(ret)) {
                            pr_warn("vfs: proc_open failed for tid %ld path '%s': %s",
                                msg.src,
                                msg.vfs.open.path,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                        } else {
                            ret = proc_watch(msg.src);
                            if (is_err(ret)) {
                                pr_warn("vfs: proc_watch failed for tid %ld: %s",
                                    msg.src,
                                    strerr(ret));
                                rpc_reply_result(msg.src, ret);
                                break;
                            }
                            resp.vfs.type = VFS_OPEN_RESP;
                            resp.vfs.open_resp.fd = fd;
                            ret = rpc_reply(msg.src, &resp);
                        }
                        break;
                    }
                    case VFS_CLOSE: {
                        ret = proc_close(
                            msg.src,
                            msg.vfs.close.fd
                        );
                        if (is_err(ret)) {
                            pr_warn("vfs: proc_close failed for tid %ld fd %ld: %s",
                                msg.src,
                                msg.vfs.close.fd,
                                strerr(ret));
                        }
                        rpc_reply_result(msg.src, ret);
                        break;
                    }
                    case VFS_READ: {
                        resp.vfs.type = VFS_READ_RESP;
                        ret = proc_read(
                            msg.src,
                            msg.vfs.read.fd,
                            resp.vfs.read_resp.data,
                            msg.vfs.read.size,
                            &resp.vfs.read_resp.size
                        );
                        if (is_err(ret)) {
                            pr_warn("vfs: proc_read failed for tid %ld fd %ld: %s",
                                msg.src,
                                msg.vfs.read.fd,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                        } else {
                            ret = rpc_reply(msg.src, &resp);
                        }
                        break;
                    }
                    case VFS_WRITE: {
                        resp.vfs.type = VFS_WRITE_RESP;
                        ret = proc_write(
                            msg.src,
                            msg.vfs.write.fd,
                            msg.vfs.write.data,
                            msg.vfs.write.size,
                            &resp.vfs.write_resp.size
                        );
                        if (is_err(ret)) {
                            pr_warn("vfs: proc_write failed for tid %ld fd %ld: %s",
                                msg.src,
                                msg.vfs.write.fd,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                        } else {
                            ret = rpc_reply(msg.src, &resp);
                        }
                        break;
                    }
                    case VFS_UNLINK: {
                        ret = proc_unlink(
                            msg.src,
                            msg.vfs.unlink.fd
                        );
                        if (is_err(ret)) {
                            pr_warn("vfs: proc_unlink failed for tid %ld fd %ld: %s",
                                msg.src,
                                msg.vfs.unlink.fd,
                                strerr(ret));
                        }
                        rpc_reply_result(msg.src, ret);
                        break;
                    }
                    default: {
                        pr_warn("vfs: received unknown vfs msg type %ld from %ld",
                            msg.vfs.type, msg.src);
                        rpc_reply_result(msg.src, -ERR_UNKNOWN_REQ);
                        break;
                    }
                }
                break;
            }
            default: {
                pr_warn("vfs: received unknown msg type %ld from %ld",
                    msg.type, msg.src);
                rpc_reply_result(msg.src, -ERR_UNKNOWN_REQ);
                break;
            }
        }
    }    

    panic("vfs server exited unexpectedly");
}
