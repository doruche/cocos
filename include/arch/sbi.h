#ifndef _ARCH_SBI_H
#define _ARCH_SBI_H 1

enum sbi_ext_id {
    SBI_EXT_0_1_SET_TIMER = 0x0,
    SBI_EXT_0_1_CONSOLE_PUTCHAR = 0x1,
    SBI_EXT_0_1_SHUTDOWN = 0x8,
};

struct sbiret {
    long error;
    long value;
};

struct sbiret sbi_ecall(int ext, int fid, unsigned long arg0,
			unsigned long arg1, unsigned long arg2,
			unsigned long arg3, unsigned long arg4,
			unsigned long arg5);

// pure sbi calls
void    sbi_console_putchar(int ch);
void    sbi_shutdown(void);

// higher level sbi calls
void    sbi_console_puts(const char* str);

#endif // !_ARCH_SBI_H