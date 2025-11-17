#include "bfs.h"
#include <libs/prelude.h>

extern u8 __bfs_img[];

static inline bfs_super_t*
bfs_sb(void) {
    return (bfs_super_t*)__bfs_img;
}

static inline bfs_inode_t*
bfs_inodes(void) {
    return (bfs_inode_t*)(__bfs_img + sizeof(bfs_super_t));
}

void
bfs_probe(void) {
    bfs_super_t* sb = bfs_sb();
    if (sb->magic != BFS_MAGIC) {
        panic("bfs: invalid magic number: 0x%x (expected 0x%x)",
            sb->magic, BFS_MAGIC);
    }
    pr_trace("bfs: detected with %ld inodes",
        sb->inode_cnt);
}

const bfs_inode_t*
bfs_lookup(const char* name) {
    bfs_super_t* sb = bfs_sb();
    bfs_inode_t* inodes = bfs_inodes();
    for (usize i = 0; i < sb->inode_cnt; i++) {
        if (strcmp(inodes[i].name, name) == 0) {
            return &inodes[i];
        }
    }
    return NULL;
}

const bfs_inode_t*
bfs_inode(usize index) {
    bfs_super_t* sb = bfs_sb();
    bfs_inode_t* inodes = bfs_inodes();
    if (index >= sb->inode_cnt) {
        pr_trace("bfs_inode: index %ld out of bounds (inode_cnt=%ld)\n",
            index, sb->inode_cnt);
        return NULL;
    }
    pr_trace("bfs_inode: index=%ld, name='%s', size=0x%lx, offset=0x%lx\n",
        index,
        inodes[index].name,
        inodes[index].size,
        inodes[index].offset
    );
    return &inodes[index];
}

const u8*
bfs_read_inplace(const bfs_inode_t* inode) {
    pr_trace("bfs_read_inplace: inode name='%s', size=0x%lx, offset=0x%lx\n",
        inode->name,
        inode->size,
        inode->offset
    );
    return __bfs_img + inode->offset;
}

usize
bfs_read(
    const bfs_inode_t* inode,
    u8* buffer,
    usize offset,
    usize len
) {
    if (offset >= inode->size) {
        return 0;
    }
    if (offset + len > inode->size) {
        len = inode->size - offset;
    }
    const u8* data_start = __bfs_img + inode->offset;
    memcpy(buffer, data_start + offset, len);
    return len;
}