    .section .text
    .globl ktrap_trampoline
    .type ktrap_trampoline, @function
    .p2align 2
ktrap_trampoline:
    # for kernel trap, we just push registers onto current stack
    addi sp, sp, -32 * 8
    sd ra, 1*8(sp)
    # do not save sp here
    sd gp, 3*8(sp)
    sd tp, 4*8(sp)
    sd t0, 5*8(sp)
    sd t1, 6*8(sp)
    sd t2, 7*8(sp)
    sd s0, 8*8(sp)
    sd s1, 9*8(sp)
    sd a0, 10*8(sp)
    sd a1, 11*8(sp)
    sd a2, 12*8(sp)
    sd a3, 13*8(sp)
    sd a4, 14*8(sp)
    sd a5, 15*8(sp)
    sd a6, 16*8(sp)
    sd a7, 17*8(sp)
    sd s2, 18*8(sp)
    sd s3, 19*8(sp)
    sd s4, 20*8(sp)
    sd s5, 21*8(sp)
    sd s6, 22*8(sp)
    sd s7, 23*8(sp)
    sd s8, 24*8(sp)
    sd s9, 25*8(sp)
    sd s10, 26*8(sp)
    sd s11, 27*8(sp)
    sd t3, 28*8(sp)
    sd t4, 29*8(sp)
    sd t5, 30*8(sp)
    sd t6, 31*8(sp)

    mv a0, sp
    call ktrap
    mv sp, a0

    # restore registers
    ld ra, 1*8(sp)
    ld gp, 3*8(sp)
    ld tp, 4*8(sp)
    ld t0, 5*8(sp)
    ld t1, 6*8(sp)
    ld t2, 7*8(sp)
    ld s0, 8*8(sp)
    ld s1, 9*8(sp)
    ld a0, 10*8(sp)
    ld a1, 11*8(sp)
    ld a2, 12*8(sp)
    ld a3, 13*8(sp)
    ld a4, 14*8(sp)
    ld a5, 15*8(sp)
    ld a6, 16*8(sp)
    ld a7, 17*8(sp)
    ld s2, 18*8(sp)
    ld s3, 19*8(sp)
    ld s4, 20*8(sp)
    ld s5, 21*8(sp)
    ld s6, 22*8(sp)
    ld s7, 23*8(sp)
    ld s8, 24*8(sp)
    ld s9, 25*8(sp)
    ld s10, 26*8(sp)
    ld s11, 27*8(sp)
    ld t3, 28*8(sp)
    ld t4, 29*8(sp)
    ld t5, 30*8(sp)
    ld t6, 31*8(sp)

    addi sp, sp, 32 * 8
    sret

    .section .text.trampoline
    .globl u_trampoline_entry
    .type u_trampoline_entry, @function
    .balign 4096
u_trampoline_entry:
    # we hold pointer to arch_ctx_t in sscratch
    csrrw sp, sscratch, sp
    # now sp -> arch_task_t, sscratch -> user sp
    
    # save registers
    sd ra, 1*8(sp)
    # do not save sp here
    sd gp, 3*8(sp)
    sd tp, 4*8(sp)
    sd t0, 5*8(sp)
    sd t1, 6*8(sp)
    sd t2, 7*8(sp)
    sd s0, 8*8(sp)
    sd s1, 9*8(sp)
    sd a0, 10*8(sp)
    sd a1, 11*8(sp)
    sd a2, 12*8(sp)
    sd a3, 13*8(sp)
    sd a4, 14*8(sp)
    sd a5, 15*8(sp)
    sd a6, 16*8(sp)
    sd a7, 17*8(sp)
    sd s2, 18*8(sp)
    sd s3, 19*8(sp)
    sd s4, 20*8(sp)
    sd s5, 21*8(sp)
    sd s6, 22*8(sp)
    sd s7, 23*8(sp)
    sd s8, 24*8(sp)
    sd s9, 25*8(sp)
    sd s10, 26*8(sp)
    sd s11, 27*8(sp)
    sd t3, 28*8(sp)
    sd t4, 29*8(sp)
    sd t5, 30*8(sp)
    sd t6, 31*8(sp)

    # store user sp
    csrr t0, sscratch
    sd t0, 2*8(sp)

    # load kernel sp
    ld sp, 32*8(sp)

    ld t0, __utrap
    jr t0



    .section .text.trampoline
    .globl u_trampoline_ret
    .type u_trampoline_ret, @function
    .align  4
u_trampoline_ret:
    # now tf.x[2] -> user sp, sscratch -> actx

    # restore user registers
    csrr sp, sscratch
    ld ra, 1*8(sp)
    # do not restore sp here
    ld gp, 3*8(sp)        
    ld tp, 4*8(sp)
    ld t0, 5*8(sp)
    ld t1, 6*8(sp)
    ld t2, 7*8(sp)
    ld s0, 8*8(sp)
    ld s1, 9*8(sp)
    ld a0, 10*8(sp)
    ld a1, 11*8(sp)
    ld a2, 12*8(sp)
    ld a3, 13*8(sp)
    ld a4, 14*8(sp)
    ld a5, 15*8(sp)
    ld a6, 16*8(sp)
    ld a7, 17*8(sp)
    ld s2, 18*8(sp)
    ld s3, 19*8(sp)
    ld s4, 20*8(sp)
    ld s5, 21*8(sp)
    ld s6, 22*8(sp)
    ld s7, 23*8(sp)
    ld s8, 24*8(sp)
    ld s9, 25*8(sp)
    ld s10, 26*8(sp)
    ld s11, 27*8(sp)
    ld t3, 28*8(sp)
    ld t4, 29*8(sp)
    ld t5, 30*8(sp)
    ld t6, 31*8(sp)
    # restore user sp
    ld sp, 2*8(sp)

    sret

    .section .text.trampoline
__utrap:
    .dword utrap