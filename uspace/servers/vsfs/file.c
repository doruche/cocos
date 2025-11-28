#include "vsfs.h"
#include <libs/prelude.h>

extern struct vsfs_super vsfs_super;

result_t
vsfs_read(u16 ino, void *buf, usize size, usize offset, usize *bytes_read) {
    struct vsfs_inode inode;
    unwrap_err(vsfs_read_inode(ino, &inode));

    if (offset >= inode.size) {
        *bytes_read = 0;
        return OK;
    }

    usize read_size = size;
    if (offset + read_size > inode.size) {
        read_size = inode.size - offset;
    }

    usize total_read = 0;
    u8 *out_buf = (u8 *)buf;

    while (total_read < read_size) {
        usize blk_idx = (offset + total_read) / vsfs_super.blocksz;
        usize blk_off = (offset + total_read) % vsfs_super.blocksz;
        usize to_read = min(read_size - total_read, vsfs_super.blocksz - blk_off);

        if (blk_idx >= VSFS_BLK_PER_INODE) {
            break; // Should not happen if size is correct
        }

        u16 phy_blk = VSFS_INO_TO_BLKNO(ino) + 1 + blk_idx;
        struct vsfs_bufhdr *bh;
        unwrap_err(vsfs_bio_read(phy_blk, &bh));

        memcpy(out_buf + total_read, bh->data + blk_off, to_read);
        total_read += to_read;
    }

    *bytes_read = total_read;
    return OK;
}

result_t
vsfs_write(u16 ino, const void *buf, usize size, usize offset, usize *bytes_written) {
    struct vsfs_inode inode;
    unwrap_err(vsfs_read_inode(ino, &inode));

    usize total_written = 0;
    const u8 *in_buf = (const u8 *)buf;

    while (total_written < size) {
        usize blk_idx = (offset + total_written) / vsfs_super.blocksz;
        usize blk_off = (offset + total_written) % vsfs_super.blocksz;
        usize to_write = min(size - total_written, vsfs_super.blocksz - blk_off);

        if (blk_idx >= VSFS_BLK_PER_INODE) {
            return -ERR_NOSPC;
        }

        u16 phy_blk = VSFS_INO_TO_BLKNO(ino) + 1 + blk_idx;
        struct vsfs_bufhdr *bh;
        unwrap_err(vsfs_bio_read(phy_blk, &bh));

        memcpy(bh->data + blk_off, in_buf + total_written, to_write);
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

