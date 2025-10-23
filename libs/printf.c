#include "libs/printf.h"
#include "libs/types.h"
#include "libs/panic.h"
#include <stdarg.h>

#define panic __panic

static usize
__putc(char c) {
    char buf[2];
    buf[0] = c;
    buf[1] = '\0';
    __puts(buf);
    return 1;
}

static usize
print_str(const char* str) { 
    if (str == NULL) {
        return print_str("(null)");
    }
    
    usize len = 0;
    while(str[len]) {
        __putc(str[len]);
        len++;
    }
    return len;
}

static usize
print_int(i64 num, u8 base, bool is_signed, bool pad) {
    static const char* digits = "0123456789abcdef";

    if (base != 2 && base != 8 && base != 10 && base != 16) {
        panic("print_int: unsupported base"); 
    }
    
    u64 abs_num;
    char sign = 0;

    if (is_signed && num < 0) {
        sign = '-';
        abs_num = -(u64)num; 
    } else {
        abs_num = (u64)num;
    }

    if (abs_num == 0) {
        return __putc('0'); 
    }

    char buf[65] = {0};
    usize i = 0;

    while (abs_num > 0) {
        buf[i++] = digits[abs_num % base];
        abs_num /= base;
    }

    usize total_len = i;
    if (sign) {
        total_len++;
    }

    int printed_len = 0;
    if (sign) {
        printed_len += __putc(sign);
    }

    if (pad && total_len < 16) {
        // riscv64
        for (int k = 0; k < 16 - total_len; k++) {
            printed_len += __putc('0');
        }
    }

    for (usize j = i; j > 0; j--) {
        printed_len += __putc(buf[j - 1]);
    }
    
    return printed_len;
}

isize
vprintf(const char* fmt, va_list ap)  {
    // currently for error cases we just panic,
    // so actually we never return -1.
    
    isize printed = 0;
    for (usize i = 0; fmt[i]; i++) {
        if (fmt[i] == '%') {
            i++;
            switch (fmt[i]) {
                case 'l': {
                    i++;
                    if (fmt[i] == 'd') {
                        i64 num = va_arg(ap, i64);
                        printed += print_int(num, 10, true, false);
                    } else if (fmt[i] == 'x') {
                        u64 num = va_arg(ap, u64);
                        printed += print_int(num, 16, false, false);
                    } else if (fmt[i] == 'b') {
                        u64 num = va_arg(ap, u64);
                        printed += print_int(num, 2, false, false);
                    } else if (fmt[i] == 'o') {
                        u64 num = va_arg(ap, u64);
                        printed += print_int(num, 8, false, false);
                    } else {
                        panic("vprintf: unsupported format specifier after 'l'");
                    }
                    break;
                }
                case 'd': {
                    i64 num = (i64)va_arg(ap, i32);
                    printed += print_int(num, 10, true, false);
                    break;
                }
                case 'x': {
                    u64 num = (u64)va_arg(ap, u32);
                    printed += print_int(num, 16, false, false);
                    break;
                }
                case 'b': {
                    u64 num = (u64)va_arg(ap, u32);
                    printed += print_int(num, 2, false, false);
                    break;
                }
                case 'o': {
                    u64 num = (u64)va_arg(ap, u32);
                    printed += print_int(num, 8, false, false);
                    break;
                }
                case 's': {
                    const char* str = va_arg(ap, const char*);
                    printed += print_str(str);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(ap, int); // char is promoted to int in va_arg
                    printed += __putc(c);
                    break;
                }
                case 'p': {
                    void* ptr = va_arg(ap, void*);
                    printed += print_str("0x");
                    printed += print_int((usize)ptr, 16, false, true);
                    break;
                }
                case '%': {
                    printed += __putc('%');
                    break;
                }
                default: {
                    panic("vprintk: unsupported format specifier");
                    // return -1;
                }
            }
        } else {
            printed += __putc(fmt[i]);
        }
    }
    return printed;
}

isize
printf(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    isize ret = vprintf(fmt, ap);
    va_end(ap);
    return ret;
}
