    .section    .text.entry
     .globl      _start
     .type       _start, @function
_start:
    mv fp, zero
    mv ra, zero

    # load argc and argv
    
    # If *sp == NULL, then we should move up by 8 bytes,
    # cz argc is at least 1 (program path itself)
    ld t0, 0(sp)
    mv t1, sp
    beqz t0, add8
    j add8done
add8:
    ld t0, 8(sp)
    addi t1, t1, 8
add8done:
    mv a0, t0   # argc
    addi a1, t1, 8  # argv

    mv t0, zero
    mv t1, zero

    j crt0