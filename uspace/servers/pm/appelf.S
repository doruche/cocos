    .section .rodata
    .globl __app_elf
__app_elf:
    .incbin "../build/uspace/apps/hello/hello.elf"