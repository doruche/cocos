#include "vsfs.h"
#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/fd.h>

extern const char* dev;
struct vsfs_super vsfs_super;

result_t
vsfs_mount(void) {
    u64 fd = -1;
    result_t ret = open(dev, O_RDONLY, &fd);
    if (is_err(ret)) {
        goto done;
    }
    stat_t st;
    ret = fstat(fd, &st);
    if (is_err(ret)) {
        goto done;
    }
    vsfs_super.nblocks = st.size / st.blksize;
    vsfs_super.blocksz = (u16)st.blksize;

    vsfs_bio_init();

    struct vsfs_bufhdr* bh;
    ret = vsfs_bio_read(0, &bh);
    if (is_err(ret)) {
        goto done;
    }
    struct vsfs_super* dsuper = (struct vsfs_super*)bh->data;
    if (dsuper->magic != VSFS_MAGIC) {
        printf("vsfs_mount: invalid magic: 0x%x\n", dsuper->magic);
        goto done;
    }
    assert_eq(vsfs_super.blocksz, dsuper->blocksz);
    assert_eq(vsfs_super.nblocks, dsuper->nblocks);
    vsfs_super.magic = dsuper->magic;
    vsfs_super.ninodes = dsuper->ninodes;

done:
    if (fd != (u64)-1) {
        unwrap_err(close(fd));
    }
    return ret;
}

result_t
vsfs_alloc_inode(u16 *out) {
    for (u16 ino = 0; ino < vsfs_super.ninodes; ino++) {
        struct vsfs_bufhdr* bh;
        unwrap_err(vsfs_bio_read(VSFS_INO_TO_BLKNO(ino), &bh));
        struct vsfs_inode* inode = (struct vsfs_inode*)bh->data;
        if (!inode->in_use) {
            inode->in_use = true;
            inode->size = 0;
            memset(inode->blocks, 0, sizeof(inode->blocks));
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
    unwrap_err(vsfs_bio_read(VSFS_INO_TO_BLKNO(ino), &bh));
    struct vsfs_inode* inode = (struct vsfs_inode*)bh->data;
    inode->in_use = false;
    bh->dirty = true;
    return OK;
}

result_t
vsfs_umount(void) {
    u8 buf[vsfs_super.blocksz];
    memcpy(buf, &vsfs_super, sizeof(vsfs_super));
    unwrap_err(vsfs_bio_write(0, buf));
    unwrap_err(vsfs_bio_sync());
    return OK;
}
