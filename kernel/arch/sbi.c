#include "arch/sbi.h"
#include "types.h"

/*
 * SBI (Supervisor Binary Interface) environment call.
 * Adapted from linux kernel: https://elixir.bootlin.com/linux/v6.6.32/source/arch/riscv/kernel/sbi.c
 */

struct sbiret sbi_ecall(int ext, int fid, unsigned long arg0,
			unsigned long arg1, unsigned long arg2,
			unsigned long arg3, unsigned long arg4,
			unsigned long arg5)
{
	struct sbiret ret;

	register u64 a0 asm ("a0") = (u64)(arg0);
	register u64 a1 asm ("a1") = (u64)(arg1);
	register u64 a2 asm ("a2") = (u64)(arg2);
	register u64 a3 asm ("a3") = (u64)(arg3);
	register u64 a4 asm ("a4") = (u64)(arg4);
	register u64 a5 asm ("a5") = (u64)(arg5);
	register u64 a6 asm ("a6") = (u64)(fid);
	register u64 a7 asm ("a7") = (u64)(ext);
	asm volatile ("ecall"
		      : "+r" (a0), "+r" (a1)
		      : "r" (a2), "r" (a3), "r" (a4), "r" (a5), "r" (a6), "r" (a7)
		      : "memory");
	ret.error = a0;
	ret.value = a1;

	return ret;
}

void
sbi_console_putchar(int ch) {
    sbi_ecall(SBI_EXT_0_1_CONSOLE_PUTCHAR, 0, (unsigned long)(ch),
          0, 0, 0, 0, 0);
}

void
sbi_console_puts(const char* str) {
    while (*str) {
        sbi_console_putchar(*str++);
    }
}


void
sbi_shutdown(void) {
    sbi_ecall(SBI_EXT_0_1_SHUTDOWN, 0, 0, 0, 0, 0, 0, 0);
}