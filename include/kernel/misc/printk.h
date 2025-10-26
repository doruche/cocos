/*
 * print a kernel message.
 */
#pragma once

#include "libs/prelude.h"
#include <stdarg.h>

isize vprintk(const char* fmt, va_list ap);
isize printk(const char *fmt, ...);

