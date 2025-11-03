/*
 * pm needs a way to start/reincarnate initial servers
 * without relying on the filesystem server.
 * bfs(boot file system) serves this purpose by embedding the ELF binaries
 * of the initial servers directly into the PM binary,
 * and provides a neat interface to access them.
 * this is just a minimal, linear and read-only filesystem,
 * without any hierarchy or advanced features.
 * cz there is no underlying block device, the logic can be quite simple.
 * 
 * layout: superblock | inodes | file data
 */

#pragma once

#include "libs/prelude.h"

#define BFS_MAGIC       0x00736662 // "bfs\0"

typedef struct {
    union {
        struct {
            u32 magic;
            u32 inode_cnt;
        };
        u8 padding[16];
    };
} bfs_super_t;

typedef struct {
    union {
        struct {
            char name[16];
            u32 size;
            u32 offset; // data offset from the start of the bfs image
        };
        u8 padding[32];
    };
} bfs_inode_t;


void bfs_probe(void);
const bfs_inode_t* bfs_lookup(const char* name);
const bfs_inode_t* bfs_inode(usize index);
const u8* bfs_read_inplace(const bfs_inode_t* inode);
usize bfs_read(
    const bfs_inode_t* inode,
    u8* buffer,
    usize offset,
    usize len
);