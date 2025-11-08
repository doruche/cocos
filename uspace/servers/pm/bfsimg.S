    .section .rodata
    .globl __bfs_img
    .balign 4096
__bfs_img:
    .incbin "../build/uspace/bfs.img"