    .section    .text.entry
     .globl      _start
     .type       _start, @function
_start:
    mv fp, zero
    mv ra, zero

    j crt0