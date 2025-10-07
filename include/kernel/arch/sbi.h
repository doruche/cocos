/*
 * SBI (Supervisor Binary Interface) related definitions.
 */

#ifndef _K_ARCH_SBI_H
#define _K_ARCH_SBI_H 1

#include "libs/types.h"

enum sbi_ext_id {
    SBI_EXT_0_1_SET_TIMER = 0x0,
    SBI_EXT_0_1_CONSOLE_PUTCHAR = 0x1,
    SBI_EXT_0_1_SHUTDOWN = 0x8,
};

struct sbiret {
    isize error;
    isize value;
};

struct sbiret sbi_ecall(i32 ext, i32 fid, u64 arg0,
			u64 arg1, u64 arg2,
			u64 arg3, u64 arg4,
			u64 arg5);

// pure sbi calls
void    sbi_console_putchar(char ch);
void    sbi_set_timer(u64 timecmp);
void    sbi_shutdown(void);


// higher level sbi calls
void    sbi_console_puts(const char* str);

#endif // !_K_ARCH_SBI_H