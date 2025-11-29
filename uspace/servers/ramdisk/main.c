#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/task.h>

/* meaningless. */
#define RAMDISK_HANDLE 42

static u8* ramdisk = NULL;
static usize nblock = 0;
static usize block_size = 0;

static result_t
ramdisk_blk_read(usize blkno, void *buf) {
    if (blkno >= nblock) {
        return -ERR_OUT_OF_BOUNDS;
    }
    memcpy(buf, ramdisk + blkno * block_size, block_size);
    return OK;
}
static result_t
ramdisk_blk_write(usize blkno, const void *buf) {
    if (blkno >= nblock) {
        return -ERR_OUT_OF_BOUNDS;
    }
    memcpy(ramdisk + blkno * block_size, buf, block_size);
    return OK;
}

result_t
main(usize argc, char **argv) {
    if (argc != 4) {
        printf("usage: %s <dev_name> <nblocks> <block_size>\n", argv[0]);
        return -ERR_INVAL;
    }
    const char *dev_name = argv[1];
    if (is_err(str2isize(argv[2], (isize*)&nblock)) ||
        is_err(str2isize(argv[3], (isize*)&block_size))) {
        printf("invalid nblocks or block_size\n");
        return -ERR_INVAL;
    }

    if (nblock == 0 || block_size == 0) {
        printf("nblocks and block_size must be greater than 0\n");
        return -ERR_INVAL;
    }

    if (block_size % 512 != 0) {
        printf("block_size must be a multiple of 512\n");
        return -ERR_INVAL;
    }

    if (block_size > 1024 * 1024) {
        printf("block_size too large\n");
        return -ERR_INVAL;
    }

    if ((ramdisk = malloc(nblock * block_size)) == NULL) {
        printf("failed to allocate ramdisk memory\n");
        return -ERR_NOMEM;
    }

    unwrap_err(pns_publish(dev_name));
    pr_info("ramdisk %s started: %ld blocks, block size %ld bytes\n",
        dev_name, nblock, block_size);

    loop {
        msg_t msg = {0};
        msg_t resp = {0};
        result_t ret = ipc_recv(IPC_OPEN, &msg);
        if (is_err(ret)) {
            pr_warn("ramdisk: ipc_recv failed: %s",
                strerr(ret));
            continue;
        }
        switch (msg.type) {
            case MSG_FS: {
                switch (msg.fs.type) {
                    resp.type = MSG_FS;
                    case FS_GET: {
                        if (strcmp(msg.fs.get.path, "/") != 0) {
                            pr_warn("ramdisk: invalid get path %s",
                                msg.fs.get.path);
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                        resp.fs.type = FS_GET_RESP;
                        /* only one ramdisk. we do not check handle actually */
                        resp.fs.get_resp.handle = RAMDISK_HANDLE;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_READ: {
                        if (msg.fs.read.handle != RAMDISK_HANDLE) {
                            pr_warn("ramdisk: invalid handle %ld",
                                msg.fs.read.handle);
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                        /* for disk we disallow unaligned requests */
                        if (msg.fs.read.size != block_size ||
                            msg.fs.read.offset % block_size != 0) {
                            pr_warn("ramdisk: unaligned read request");
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                        usize blkno = msg.fs.read.offset / block_size;
                        resp.fs.type = FS_READ_RESP;
                        ret = ramdisk_blk_read(
                            blkno,
                            resp.fs.read_resp.data
                        );
                        if (is_err(ret)) {
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.fs.read_resp.size = block_size;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_WRITE: {
                        if (msg.fs.write.handle != RAMDISK_HANDLE) {
                            pr_warn("ramdisk: invalid handle %ld",
                                msg.fs.write.handle);
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                        if (msg.fs.write.size != block_size ||
                            msg.fs.write.offset % block_size != 0) {
                            pr_warn("ramdisk: unaligned write request");
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                        usize blkno = msg.fs.write.offset / block_size;
                        ret = ramdisk_blk_write(
                            blkno,
                            msg.fs.write.data
                        );
                        if (is_err(ret)) {
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.fs.type = FS_WRITE_RESP;
                        resp.fs.write_resp.size = block_size;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_STAT:
                        if (strcmp(msg.fs.stat.path, "/") != 0) {
                            pr_warn("ramdisk: invalid stat path %s",
                                msg.fs.stat.path);
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                    case FS_FSTAT: {
                        if (msg.fs.type == FS_FSTAT &&
                            msg.fs.fstat.handle != RAMDISK_HANDLE) {
                            pr_warn("ramdisk: invalid handle %ld",
                                msg.fs.fstat.handle);
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                        resp.fs.type = FS_STAT_RESP;
                        stat_init(&resp.fs.stat_resp.stat);
                        resp.fs.stat_resp.stat.mode = S_IFBLK;
                        resp.fs.stat_resp.stat.blksize = block_size;
                        resp.fs.stat_resp.stat.blocks = nblock;
                        resp.fs.stat_resp.stat.size = nblock * block_size;
                        resp.fs.stat_resp.stat.dev = task_gettid();
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_UNLINK:
                    case FS_MKDIR:
                    case FS_RMDIR:
                    case FS_READDIR: {
                        rpc_reply_result(msg.src, -ERR_NOT_SUPPORTED);
                        break;
                    }
                    default: {
                        pr_warn("ramdisk: unknown FS message type %d from tid %ld",
                            msg.fs.type, msg.src);
                        rpc_reply_result(msg.src, -ERR_UNKNOWN_REQ);    
                        break;
                    }
                }
                break;
            }
            default: {
                pr_warn("ramdisk: unknown message type %ld from tid %ld",
                    msg.type, msg.src);
                rpc_reply_result(msg.src, -ERR_UNKNOWN_REQ);
                break;
            }
        }
    }

    pr_info("ramdisk %s exiting\n", dev_name);
    return OK;
}