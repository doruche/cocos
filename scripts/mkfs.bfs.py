#!/usr/bin/env python3

'''
mkfs.bfs.py
Simple script to create a bfs image.
Layout: superblock | inodes | file data
See uspace/servers/pm/bfs.h for structure definitions.
Usage: mkfs.bfs.py -o <output_path> <file1> <file2> ...
'''

import struct
import argparse

BFS_MAGIC = 0x00736662  # "bfs\0"
BFS_NAME_MAX = 16
BFS_INODE_SIZE = 32
BFS_SUPER_SIZE = 16

def align_up(x, align):
    return (x + align - 1) & ~(align - 1)

def main():
    parser = argparse.ArgumentParser(description='Create a BFS filesystem image.')
    parser.add_argument('-o', '--output', required=True, help='Output BFS image file path')
    parser.add_argument('-s', '--silent', action='store_true', help='Suppress output messages')
    parser.add_argument('files', nargs='*', help='Files to include in the BFS image')
    args = parser.parse_args()

    inodes = []
    inode_cnt = len(args.files)
    filedatas = []
    offset = BFS_SUPER_SIZE + inode_cnt * BFS_INODE_SIZE
    assert offset % 16 == 0, "Offset must be aligned to 16 bytes"
    
    for filepath in args.files:
        with open(filepath, 'rb') as f:
            data = f.read()
        name = filepath.split('/')[-1].encode('ascii')
        if len(name) > BFS_NAME_MAX:
            raise ValueError(f"Filename {name} too long (max {BFS_NAME_MAX} bytes)")
        size = len(data)
        inodes.append((name.ljust(BFS_NAME_MAX, b'\0'), size, offset))
        filedatas.append(data)
        offset += align_up(size, 16)

    bfs_img = bytearray()
    bfs_img += struct.pack('<I I 8x', BFS_MAGIC, inode_cnt)

    for name, size, offset in inodes:
        bfs_img += struct.pack('<16s I I 8x', name, size, offset)

    offset = BFS_SUPER_SIZE + inode_cnt * BFS_INODE_SIZE
    for data in filedatas:
        bfs_img += data
        offset += len(data)
        if offset % 16 != 0:
            padding = 16 - (offset % 16)
            bfs_img += b'\0' * padding
            offset += padding

    with open(args.output, 'wb') as f:
        f.write(bfs_img)

    if not args.silent:
        print(f"bfs image created at {args.output} with {inode_cnt} files.")
        for name, size, offset in inodes:
            print(f" - {name.decode('ascii')}: size=0x{size:x}, offset=0x{offset:x}")

if __name__ == '__main__':
    main()