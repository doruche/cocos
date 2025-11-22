#include "libs/hooks.h"
#include "libs/prelude.h"

typedef struct _printf_ctx_t {
    void (*putc)(struct _printf_ctx_t*, char);
    usize nprinted;
    
    /* for snprintf */
    char* buf;
    usize size;
} printf_ctx_t;

static char console_buf[256];
static usize console_buf_index = 0;

void
console_flush(void) {
    usize len = console_buf_index;
    if (len > 0) {
        console_buf[console_buf_index] = '\0';
        hook_call(puts, console_buf);
        console_buf_index = 0;
    }
}

static void
console_putc(printf_ctx_t* ctx, char c) {
    if (console_buf_index >= sizeof(console_buf) - 1) {
        console_flush();
    }
    console_buf[console_buf_index++] = c;
    if (c == '\n') {
        console_flush();
    }
    ctx->nprinted++;
}

static void
string_putc(printf_ctx_t* ctx, char c) {
    if (ctx->nprinted < ctx->size - 1) {
        ctx->buf[ctx->nprinted] = c;
    }
    ctx->nprinted++;
}

static void
generic_putc(printf_ctx_t* ctx, char c) {
    ctx->putc(ctx, c);
}

static usize
print_str(printf_ctx_t* ctx, const char* str) { 
    if (str == NULL) {
        return print_str(ctx, "(null)");
    }
    
    usize len = 0;
    while(str[len]) {
        generic_putc(ctx, str[len]);
        len++;
    }
    return len;
}

static usize
print_int(printf_ctx_t* ctx, i64 num, u8 base, bool is_signed, bool pad) {
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
        generic_putc(ctx, '0');
        return 1;
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
        generic_putc(ctx, sign);
        printed_len++;
    }

    if (pad && total_len < 16) {
        // riscv64
        for (int k = 0; k < 16 - total_len; k++) {
            generic_putc(ctx, '0');
            printed_len++;
        }
    }

    for (usize j = i; j > 0; j--) {
        generic_putc(ctx, buf[j - 1]);
        printed_len++;
    }
    
    return printed_len;
}

static isize
vprintf_generic(printf_ctx_t* ctx, const char* fmt, va_list ap)  {
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
                        printed += print_int(ctx, num, 10, true, false);
                    } else if (fmt[i] == 'x') {
                        u64 num = va_arg(ap, u64);
                        printed += print_int(ctx, num, 16, false, false);
                    } else if (fmt[i] == 'b') {
                        u64 num = va_arg(ap, u64);
                        printed += print_int(ctx, num, 2, false, false);
                    } else if (fmt[i] == 'o') {
                        u64 num = va_arg(ap, u64);
                        printed += print_int(ctx, num, 8, false, false);
                    } else {
                        panic("vprintf: unsupported format specifier after 'l'");
                    }
                    break;
                }
                case 'd': {
                    i64 num = (i64)va_arg(ap, i32);
                    printed += print_int(ctx, num, 10, true, false);
                    break;
                }
                case 'x': {
                    u64 num = (u64)va_arg(ap, u32);
                    printed += print_int(ctx, num, 16, false, false);
                    break;
                }
                case 'b': {
                    u64 num = (u64)va_arg(ap, u32);
                    printed += print_int(ctx, num, 2, false, false);
                    break;
                }
                case 'o': {
                    u64 num = (u64)va_arg(ap, u32);
                    printed += print_int(ctx, num, 8, false, false);
                    break;
                }
                case 's': {
                    const char* str = va_arg(ap, const char*);
                    printed += print_str(ctx, str);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(ap, int); // char is promoted to int in va_arg
                    generic_putc(ctx, c);
                    printed++;
                    break;
                }
                case 'p': {
                    void* ptr = va_arg(ap, void*);
                    printed += print_str(ctx, "0x");
                    printed += print_int(ctx, (usize)ptr, 16, false, true);
                    break;
                }
                case '%': {
                    generic_putc(ctx, '%');
                    printed++;
                    break;
                }
                default: {
                    panic("vprintk: unsupported format specifier");
                    // return -1;
                }
            }
        } else {
            generic_putc(ctx, fmt[i]);
            printed++;
        }
    }
    return printed;
}

isize
vprintf(const char* fmt, va_list ap) {
    printf_ctx_t ctx = {
        .putc = console_putc,
        .nprinted = 0,
    };
    return vprintf_generic(&ctx, fmt, ap);
}

isize
printf(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    isize ret = vprintf(fmt, ap);
    va_end(ap);
    return ret;
}

isize
vsnprintf(char *buf, usize size, const char *fmt, va_list ap) {
    printf_ctx_t ctx = {
        .putc = string_putc,
        .nprinted = 0,
        .buf = buf,
        .size = size,
    };
    isize ret = vprintf_generic(&ctx, fmt, ap);
    if (size > 0) {
        if (ctx.nprinted < size) {
            buf[ctx.nprinted] = '\0';
        } else {
            buf[size - 1] = '\0';
        }
    }
    return ret;
}

isize
snprintf(char *buf, usize size, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    isize ret = vsnprintf(buf, size, fmt, ap);
    va_end(ap);
    return ret;
}
