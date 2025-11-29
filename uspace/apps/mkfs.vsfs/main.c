#include <libs/prelude.h>
#include <uspace/fd.h>

#define VSFS_MAGIC 0x53465356  // "VSFS"

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
};
struct vsfs_dirent {
    char name[28];
    u16 mode;
    u16 ino;
};

result_t
main(usize argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: mkfs.vsfs <dev>\n");
        return -ERR_INVAL;
    }

    const char* dev = argv[1];
    u64 fd;
    unwrap_err(open(dev, O_RDWR, &fd));
    stat_t st;
    unwrap_err(fstat(fd, &st));

    u8 buf[st.blksize];
    /* write super */
    struct vsfs_super super = {
        .magic = VSFS_MAGIC,
        .blocksz = st.blksize,
        .nblocks = st.blocks,
        .ninodes = (st.blocks - 1) / 4, /* minus 1 for superblock */
    };
    pr_info("mkfs.vsfs: creating vsfs on %s with %d inodes, %d blocks, block size %d",
        dev, super.ninodes, super.nblocks, super.blocksz);
    memcpy(buf, &super, sizeof(super));
    usize bytes_written = 0;
    unwrap_err(lseek(fd, 0, SEEK_SET));
    unwrap_err(write(
        fd,
        buf,
        st.blksize,
        &bytes_written
    ));
    assert_eq(bytes_written, st.blksize);

    /* write root inode */
    struct vsfs_inode root = {
        .in_use = true,
        .size = 2 * sizeof(struct vsfs_dirent),
        .nlinks = 2,
        .mode = S_IFDIR,
    };
    memset(buf, 0, st.blksize);
    memcpy(buf, &root, sizeof(root));
    unwrap_err(lseek(fd, super.blocksz, SEEK_SET));
    unwrap_err(write(
        fd,
        buf,
        st.blksize,
        &bytes_written
    ));
    assert_eq(bytes_written, st.blksize);
    /* write . and .. entries */
    struct vsfs_dirent entries[] = {
        { .ino = 0, .mode = S_IFDIR },
        { .ino = 0, .mode = S_IFDIR }
    };
    strncpy(entries[0].name, ".", sizeof(entries[0].name));
    strncpy(entries[1].name, "..", sizeof(entries[1].name));
    memset(buf, 0, st.blksize);
    memcpy(buf, entries, sizeof(entries));
    unwrap_err(lseek(fd, super.blocksz * 2, SEEK_SET));
    unwrap_err(write(
        fd,
        buf,
        st.blksize,
        &bytes_written
    ));
    assert_eq(bytes_written, st.blksize);

    /* read back inode for testing */
    struct vsfs_inode test;
    unwrap_err(lseek(fd, super.blocksz, SEEK_SET));
    usize bytes_read = 0;
    unwrap_err(read(
        fd,
        buf,
        st.blksize,
        &bytes_read
    ));
    assert_eq(bytes_read, st.blksize);
    memcpy(&test, buf, sizeof(test));
    assert_eq(test.in_use, true);
    assert_eq(test.size, 2 * sizeof(struct vsfs_dirent));
    assert_eq(test.nlinks, 2);
    assert_eq(test.mode, S_IFDIR);

    unwrap_err(close(fd));
    
    return OK;
}