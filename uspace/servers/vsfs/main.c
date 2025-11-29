#include "vsfs.h"
#include <libs/prelude.h>
#include <libs/path.h>
#include <uspace/ipc.h>

extern struct vsfs_super vsfs_super;

result_t
main(usize argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: vsfs <dev> <name>\n");
        return -ERR_INVAL;
    }

    extern const char* dev;
    dev = argv[1];
    const char* fs_name = argv[2];

    result_t ret = vsfs_mount();
    if (is_err(ret)) {
        printf("vsfs: failed to mount filesystem on %s: %s\n",
            dev,
            strerr(ret));
        return ret;
    }
    unwrap_err(pns_publish(fs_name));
    
    loop {
        msg_t msg = {0};
        ret = ipc_recv(IPC_OPEN, &msg);
        if (is_err(ret)) {
            pr_warn("vsfs: ipc_recv failed: %s",
                strerr(ret));
            continue;
        }
        msg_t resp = {0};
        switch (msg.type) {
            case MSG_FS: {
                resp.type = MSG_FS;
                switch (msg.fs.type) {
                    case FS_GET: {
                        struct vsfs_dirent dirent;
                        ret = vsfs_resolve_path(msg.fs.get.path, &dirent);
                        if (is_err(ret)) {
                            pr_warn("vsfs: vsfs_resolve_path failed for path %s: %s",
                                msg.fs.get.path,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.fs.type = FS_GET_RESP;
                        resp.fs.get_resp.handle = dirent.ino;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_CREATE: {
                        u16 new_ino;
                        char parent[PATH_MAX_LEN];
                        path_dupparent(msg.fs.create.path, parent);
                        struct vsfs_dirent parent_dirent;
                        ret = vsfs_resolve_path(parent, &parent_dirent);
                        if (is_err(ret)) {
                            pr_warn("vsfs: vsfs_resolve_path failed for parent path %s: %s",
                                parent,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        ret = vsfs_create(
                            parent_dirent.ino,
                            path_basename(msg.fs.create.path),
                            msg.fs.create.mode,
                            &new_ino
                        );
                        if (is_err(ret)) {
                            pr_warn("vsfs: vsfs_create failed for path %s: %s",
                                msg.fs.create.path,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.fs.type = FS_CREATE_RESP;
                        resp.fs.create_resp.handle = new_ino;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_READ: {
                        u16 ino = (u16)msg.fs.read.handle;
                        usize to_read = min(FS_MAX_IO_SIZE, msg.fs.read.size);
                        usize bytes_read;
                        ret = vsfs_read(
                            ino,
                            resp.fs.read_resp.data,
                            to_read,
                            msg.fs.read.offset,
                            &bytes_read
                        );
                        if (is_err(ret)) {
                            pr_warn("vsfs: vsfs_read failed for ino %d: %s",
                                ino,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.fs.type = FS_READ_RESP;
                        resp.fs.read_resp.size = bytes_read;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_WRITE: {
                        u16 ino = (u16)msg.fs.write.handle;
                        usize to_write = min(FS_MAX_IO_SIZE, msg.fs.write.size);
                        usize bytes_written;
                        ret = vsfs_write(
                            ino,
                            msg.fs.write.data,
                            to_write,
                            msg.fs.write.offset,
                            &bytes_written
                        );
                        if (is_err(ret)) {
                            pr_warn("vsfs: vsfs_write failed for ino %d: %s",
                                ino,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.fs.type = FS_WRITE_RESP;
                        resp.fs.write_resp.size = bytes_written;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_READDIR: {
                        u16 dir_ino = (u16)msg.fs.readdir.handle;
                        struct vsfs_dirent dirent;
                        usize next_offset;
                        ret = vsfs_readdir(
                            dir_ino,
                            msg.fs.readdir.offset,
                            &dirent,
                            &next_offset
                        );
                        if (is_err(ret)) {
                            pr_warn("vsfs: vsfs_readdir failed for ino %d: %s",
                                dir_ino,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.fs.type = FS_READDIR_RESP;
                        strncpy(
                            resp.fs.readdir_resp.dirent.name,
                            dirent.name,
                            sizeof(dirent.name)
                        );
                        resp.fs.readdir_resp.next_offset = next_offset;
                        resp.fs.readdir_resp.dirent.ino = dirent.ino;
                        resp.fs.readdir_resp.dirent.mode = dirent.mode;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_SYNC: {
                        if (msg.fs.sync.umount) {
                            unwrap_err(vsfs_umount());
                            pr_info("vsfs: unmounted filesystem on %s", dev);
                            rpc_reply_result(msg.src, OK);
                            goto exit;
                        } else {
                            unwrap_err(vsfs_bio_sync());
                            rpc_reply_result(msg.src, OK);
                        }
                        break;
                    }
                    case FS_STAT: {
                        struct vsfs_dirent dirent;
                        ret = vsfs_resolve_path(
                            msg.fs.stat.path,
                            &dirent
                        );
                        if (is_err(ret)) {
                            pr_warn("vsfs: vsfs_resolve_path failed for path %s: %s",
                                msg.fs.stat.path,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        struct vsfs_inode inode;
                        unwrap_err(vsfs_read_inode(dirent.ino, &inode));
                        resp.fs.type = FS_STAT_RESP;
                        stat_init(&resp.fs.stat_resp.stat);
                        resp.fs.stat_resp.stat.mode = inode.mode;
                        resp.fs.stat_resp.stat.size = inode.size;
                        resp.fs.stat_resp.stat.nlink = inode.nlinks;
                        resp.fs.stat_resp.stat.blksize = vsfs_super.blocksz;
                        resp.fs.stat_resp.stat.blocks =
                            align_up(inode.size, vsfs_super.blocksz) / vsfs_super.blocksz;
                        resp.fs.stat_resp.stat.dev = TID_INVALID;
                        resp.fs.stat_resp.stat.ino = dirent.ino;
                        rpc_reply(msg.src, &resp);
                        break;   
                    }
                    case FS_FSTAT: {
                        u16 ino = (u16)msg.fs.fstat.handle;
                        struct vsfs_inode inode;
                        ret = vsfs_read_inode(ino, &inode);
                        if (is_err(ret)) {
                            pr_warn("vsfs: vsfs_read_inode failed for ino %d: %s",
                                ino,
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.fs.type = FS_STAT_RESP;
                        stat_init(&resp.fs.stat_resp.stat);
                        resp.fs.stat_resp.stat.mode = inode.mode;
                        resp.fs.stat_resp.stat.size = inode.size;
                        resp.fs.stat_resp.stat.nlink = inode.nlinks;
                        resp.fs.stat_resp.stat.blksize = vsfs_super.blocksz;
                        resp.fs.stat_resp.stat.blocks =
                            align_up(inode.size, vsfs_super.blocksz) / vsfs_super.blocksz;
                        resp.fs.stat_resp.stat.dev = TID_INVALID; /* TODO */ 
                        resp.fs.stat_resp.stat.ino = ino;
                        rpc_reply(msg.src, &resp);
                        break; 
                    }
                    default: {
                        pr_warn("vsfs: unknown fs msg type %ld from %ld",
                            msg.fs.type,
                            msg.src);
                        rpc_reply_result(msg.src, -ERR_UNKNOWN_REQ);
                        break;
                    }
                }
                break;
            }
            default: {
                pr_warn("vsfs: unknown msg type %ld from %ld",
                    msg.type,
                    msg.src);
                rpc_reply_result(msg.src, -ERR_UNKNOWN_REQ);
                break;
            }
        }
    }

exit:
    pr_info("vsfs: server exiting.");
    return OK;
}