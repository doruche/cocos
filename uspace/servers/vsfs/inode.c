#include "vsfs.h"
#include <libs/prelude.h>

extern struct vsfs_super vsfs_super;

result_t
vsfs_alloc_inode(u16 *out) {
    for (u16 ino = 0; ino < vsfs_super.ninodes; ino++) {
        struct vsfs_bufhdr* bh;
        unwrap_err(vsfs_bio_get(VSFS_INO_TO_BLKNO(ino), &bh));
        struct vsfs_inode* inode = (struct vsfs_inode*)bh->data;
        if (!inode->in_use) {
            inode->in_use = true;
            inode->size = 0;
            bh->dirty = true;
            *out = ino;
            return OK;
        }
    }
    return -ERR_NOSPC;
}

result_t
vsfs_free_inode(u16 ino) {
    struct vsfs_bufhdr* bh;
    unwrap_err(vsfs_bio_get(VSFS_INO_TO_BLKNO(ino), &bh));
    struct vsfs_inode* inode = (struct vsfs_inode*)bh->data;
    inode->in_use = false;
    bh->dirty = true;
    return OK;
}

result_t
vsfs_read_inode(u16 ino, struct vsfs_inode *out) {
    struct vsfs_bufhdr* bh;
    unwrap_err(vsfs_bio_get(VSFS_INO_TO_BLKNO(ino), &bh));
    struct vsfs_inode* inode = (struct vsfs_inode*)bh->data;
    memcpy(out, inode, sizeof(struct vsfs_inode));
    return OK;
}

result_t
vsfs_write_inode(u16 ino, const struct vsfs_inode *inode) {
    struct vsfs_bufhdr* bh;
    unwrap_err(vsfs_bio_get(VSFS_INO_TO_BLKNO(ino), &bh));
    struct vsfs_inode* dinode = (struct vsfs_inode*)bh->data;
    memcpy(dinode, inode, sizeof(struct vsfs_inode));
    bh->dirty = true;
    return OK;
}
