#include "vsfs.h"
#include <libs/prelude.h>

result_t
vsfs_read_inode(u16 ino, struct vsfs_inode *out) {
    struct vsfs_bufhdr* bh;
    unwrap_err(vsfs_bio_read(VSFS_INO_TO_BLKNO(ino), &bh));
    struct vsfs_inode* inode = (struct vsfs_inode*)bh->data;
    memcpy(out, inode, sizeof(struct vsfs_inode));
    return OK;
}

result_t
vsfs_write_inode(u16 ino, const struct vsfs_inode *inode) {
    struct vsfs_bufhdr* bh;
    unwrap_err(vsfs_bio_read(VSFS_INO_TO_BLKNO(ino), &bh));
    struct vsfs_inode* dinode = (struct vsfs_inode*)bh->data;
    memcpy(dinode, inode, sizeof(struct vsfs_inode));
    bh->dirty = true;
    return OK;
}
