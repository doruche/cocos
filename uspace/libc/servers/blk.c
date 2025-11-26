#include <libs/prelude.h>
#include <uspace/ipc.h>

result_t
blk_get_size(
    tid_t blk_server,
    usize* out_nblock,
    usize* out_block_size
) {
    msg_t msg = {0};
    msg.type = MSG_BLK;
    msg.blk.type = BLK_GET_SIZE;

    result_t ret = rpc_call(blk_server, &msg);
    if (is_err(ret)) {
        return ret;
    }
    *out_nblock = msg.blk.get_size_resp.nblock;
    *out_block_size = msg.blk.get_size_resp.block_size;

    return OK;
}

result_t
blk_read(
    tid_t blk_server,
    u64 blkno,
    u8 *out_buf
) {
    msg_t msg = {0};
    msg.type = MSG_BLK;
    msg.blk.type = BLK_READ;
    msg.blk.read.blkno = blkno;

    result_t ret = rpc_call(blk_server, &msg);
    if (is_err(ret)) {
        return ret;
    }
    memcpy(out_buf, msg.blk.read_resp.data, 1024);

    return OK;
}

result_t
blk_write(
    tid_t blk_server,
    u64 blkno,
    const u8 *buf
) {
    msg_t msg = {0};
    msg.type = MSG_BLK;
    msg.blk.type = BLK_WRITE;
    msg.blk.write.blkno = blkno;
    memcpy(msg.blk.write.data, buf, 1024);

    result_t ret = rpc_call(blk_server, &msg);
    if (is_err(ret)) {
        return ret;
    }

    return OK;
}