/*
 * print a kernel message.
 */
#ifndef _K_MISC_PRINTK_H
#define _K_MISC_PRINTK_H 1

#include "libs/types.h"
#include <stdarg.h>

isize printk(const char *fmt, ...);
isize vprintk(const char *fmt, va_list ap);

#endif /* _K_MISC_PRINTK_H */