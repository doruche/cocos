#include <libs/prelude.h>
#include <uspace/ipc.h>

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

    unwrap_err(tns_publish(dev_name));
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
            case MSG_BLK: {
                resp.type = MSG_BLK;
                switch (msg.blk.type) {
                    case BLK_READ: {
                        ret = ramdisk_blk_read(
                            msg.blk.read.blkno,
                            resp.blk.read_resp.data
                        );
                        if (is_err(ret)) {
                            pr_warn("ramdisk: blk_read failed: %s",
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.blk.type = BLK_READ_RESP;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case BLK_WRITE: {
                        ret = ramdisk_blk_write(
                            msg.blk.write.blkno,
                            msg.blk.write.data
                        );
                        if (is_err(ret)) {
                            pr_warn("ramdisk: blk_write failed: %s",
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        rpc_reply_result(msg.src, OK);
                        break;
                    }
                    case BLK_GET_SIZE: {
                        resp.blk.type = BLK_GET_SIZE_RESP;
                        resp.blk.get_size_resp.block_size = block_size;
                        resp.blk.get_size_resp.nblock = nblock;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    default: {
                        pr_warn("ramdisk: unknown blk message type %d from tid %ld",
                            msg.blk.type, msg.src);
                        break;
                    }       
                    break;
                }
                break;
            }
            default: {
                pr_warn("ramdisk: unknown message type %ld from tid %ld",
                    msg.type, msg.src);
                break;
            }
        }
    }

    pr_info("ramdisk %s exiting\n", dev_name);
    return OK;
}