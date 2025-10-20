    .section .text
    .global __main
__main:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, 0(sp)
    addi fp, sp, 16

    call main

    ld ra, 8(sp)
    ld fp, 0(sp)
    addi sp, sp, 16

    ret