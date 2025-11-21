#include <config.h>

    .section    .text.entry
    .globl      _start
    .type       _start, @function
_start:
    # cease stack frame propagation from sbi
    mv fp, zero
    mv ra, zero

    # set up boot stack
    # a0 -> mhartid
    # a1 -> dtb
    la sp, __stack0_bottom
    addi a0, a0, 1
    li a1, BOOT_STACK_SIZE
    mul a0, a0, a1
    add sp, sp, a0

    # jump to the world of C!
    j arch_init