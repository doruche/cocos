#include "vsfs.h"
#include <libs/prelude.h>

extern struct vsfs_super vsfs_super;

result_t
vsfs_read(u16 ino, void *buf, usize size, usize offset, usize *bytes_read) {
    struct vsfs_inode inode;
    result_t ret = vsfs_read_inode(ino, &inode);
    if (is_err(ret)) {
        return ret;
    }

    if (offset >= inode.size) {
        *bytes_read = 0;
        return OK;
    }

    usize to_read = min(size, (usize)(inode.size - offset));

    usize total_read = 0;
    u8 *out_buf = (u8 *)buf;

    while (total_read < to_read) {
        usize blk_idx = (offset + total_read) / vsfs_super.blocksz;
        usize blk_off = (offset + total_read) % vsfs_super.blocksz;
        to_read = min(to_read - total_read, vsfs_super.blocksz - blk_off);

        u16 blkno = VSFS_INO_TO_BLKNO(ino) + 1 + blk_idx;
        struct vsfs_bufhdr *bh;
        unwrap_err(vsfs_bio_get(blkno, &bh));

        memcpy(out_buf + total_read, bh->data + blk_off, to_read);
        total_read += to_read;
    }

    *bytes_read = total_read;
    return OK;
}

result_t
vsfs_write(u16 ino, const void *buf, usize size, usize offset, usize *bytes_written) {
    struct vsfs_inode inode;
    result_t ret = vsfs_read_inode(ino, &inode);
    if (is_err(ret)) {
        return ret;
    }

    usize total_written = 0;

    while (total_written < size) {
        usize blk_idx = (offset + total_written) / vsfs_super.blocksz;
        usize blk_off = (offset + total_written) % vsfs_super.blocksz;
        usize to_write = min(size - total_written, vsfs_super.blocksz - blk_off);

        if (blk_idx >= VSFS_BLK_PER_INODE) {
            return -ERR_NOSPC;
        }

        u16 blkno = VSFS_INO_TO_BLKNO(ino) + 1 + blk_idx;
        struct vsfs_bufhdr *bh = NULL;
        unwrap_err(vsfs_bio_get(blkno, &bh));

        memcpy(bh->data + blk_off, buf + total_written, to_write);
        bh->dirty = true;
        total_written += to_write;
    }

    if (offset + total_written > inode.size) {
        inode.size = offset + total_written;
        unwrap_err(vsfs_write_inode(ino, &inode));
    }

    *bytes_written = total_written;
    return OK;
}
