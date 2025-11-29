#include "vsfs.h"
#include <libs/prelude.h>
#include <libs/list.h>
#include <uspace/fd.h>

const char* dev;
extern struct vsfs_super vsfs_super;

static struct vsfs_bufhdr bcache[BCACHE_SIZE];
static list_head(bcache_list);

void
vsfs_bio_init(void) {
    for (usize i = 0; i < BCACHE_SIZE; i++) {
        bcache[i].blkno = (u16)-1;
        bcache[i].dirty = false;
        bcache[i].data = unwrap_null(malloc(vsfs_super.blocksz));
        list_push_back(&bcache_list, &bcache[i].node);
    }
}

static result_t
bio_evict_one(struct vsfs_bufhdr** out) {
    list_elem_t* lru = list_pop_front(&bcache_list);
    assert(lru != NULL);
    struct vsfs_bufhdr* bh = 
        list_entry(lru, struct vsfs_bufhdr, node);
    if (bh->dirty) {
        u64 fd;
        unwrap_err(open(dev, O_WRONLY, &fd));
        unwrap_err(lseek(fd, bh->blkno * vsfs_super.blocksz, SEEK_SET));
        unwrap_err(write(fd, bh->data, vsfs_super.blocksz, NULL));
        unwrap_err(close(fd));
    }

    bh->blkno = (u16)-1;
    bh->dirty = false;
    list_push_back(&bcache_list, &bh->node);
    *out = bh;
    return OK;
}

result_t
vsfs_bio_get(u16 blkno, struct vsfs_bufhdr **out) {
    list_foreach(iter, &bcache_list) {
        struct vsfs_bufhdr* bh = 
            list_entry(iter, struct vsfs_bufhdr, node);
        if (bh->blkno == blkno) {
            /* cache hit */
            list_remove(&bh->node);
            list_push_back(&bcache_list, &bh->node);
            *out = bh;
            return OK;
        }
    }
    /* must evict */
    struct vsfs_bufhdr* bh;
    unwrap_err(bio_evict_one(&bh));
    bh->blkno = blkno;

    /* read in */
    u64 fd;
    unwrap_err(open(dev, O_RDONLY, &fd));
    unwrap_err(lseek(fd, blkno * vsfs_super.blocksz, SEEK_SET));
    unwrap_err(read(fd, bh->data, vsfs_super.blocksz, NULL));
    unwrap_err(close(fd));

    *out = bh;
    return OK;
}

result_t
vsfs_bio_write(u16 blkno, const void *buf) {
    struct vsfs_bufhdr* bh = NULL;
    unwrap_err(vsfs_bio_get(blkno, &bh));
    memcpy(bh->data, buf, vsfs_super.blocksz);
    bh->dirty = true;
    return OK;
}

result_t
vsfs_bio_sync(void) {
    u64 fd;
    unwrap_err(open(dev, O_WRONLY, &fd));
    list_foreach(iter, &bcache_list) {
        struct vsfs_bufhdr* bh = 
            list_entry(iter, struct vsfs_bufhdr, node);
        if (bh->dirty) {
            unwrap_err(lseek(fd, bh->blkno * vsfs_super.blocksz, SEEK_SET));
            unwrap_err(write(fd, bh->data, vsfs_super.blocksz, NULL));
            bh->dirty = false;
        }
    }
    unwrap_err(close(fd));
    return OK;
}
