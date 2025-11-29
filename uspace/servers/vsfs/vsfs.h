#pragma once
#include <libs/prelude.h>

/*
 * a very simple file system
 * layout:
 * superblock : [0, 1)
 * inode 0, 3 data blocks : [1, 4)
 * inode 1, 3 data blocks : [4, 7)
 * ...
 * inode N, 3 data blocks : [1 + N*4, 1 + (N+1)*4)
 * i.e., for each inode, we allocate 1 block for inode itself, and
 * N blocks for data blocks. this is way too dumb, but simple enough.
 */

#define VSFS_MAGIC 0x53465356  // "VSFS"
#define VSFS_BLK_PER_INODE 3
#define VSFS_ROOT_INO 0
#define VSFS_INO_TO_BLKNO(ino) \
    (1 + (ino) * (1 + VSFS_BLK_PER_INODE))
/*
 * u16 for nblocks. max disk size: 65535 * blocksz
 * this is sufficient for a very simple fs.
 */

struct vsfs_super {
    u32 magic;
    u16 ninodes;
    u16 nblocks;
    u16 blocksz;
};

struct vsfs_inode {
    bool in_use;
    u16 size;
    u16 nlinks;
    u16 mode;
    /* data blocks... */
};

#define VSFS_NAME_MAX_LEN 28

struct vsfs_dirent {
    char name[VSFS_NAME_MAX_LEN];
    u16 mode;
    u16 ino;
};
static_assert(sizeof(struct vsfs_dirent) == 32);

/* bio.c */
struct vsfs_bufhdr {
    u16 blkno;
    bool dirty;
    list_elem_t node; /* lru */
    u8 *data;
};
#define BCACHE_SIZE 4
void vsfs_bio_init(void);
result_t vsfs_bio_get(u16 blkno, struct vsfs_bufhdr **out);
result_t vsfs_bio_write(u16 blkno, const void *buf);
result_t vsfs_bio_sync(void);
/* super.c */
result_t vsfs_mount(void);
result_t vsfs_umount(void);
result_t vsfs_alloc_inode(u16 *out);
result_t vsfs_free_inode(u16 ino);

/* inode.c */
result_t vsfs_read_inode(u16 ino, struct vsfs_inode *out);
result_t vsfs_write_inode(u16 ino, const struct vsfs_inode *inode);

/* file.c */
result_t vsfs_read(u16 ino, void *buf, usize size, usize offset, usize *bytes_read);
result_t vsfs_write(u16 ino, const void *buf, usize size, usize offset, usize *bytes_written);

/* dir.c */
result_t vsfs_lookup(u16 dir_ino, const char *name, struct vsfs_dirent *out);
result_t vsfs_create(u16 dir_ino, const char *name, u32 mode, u16 *out_ino);
result_t vsfs_readdir(u16 dir_ino, usize offset, struct vsfs_dirent *out, usize *next_offset);
// result_t vsfs_unlink(u16 dir_ino, const char *name);
result_t vsfs_resolve_path(char *path, struct vsfs_dirent *out);