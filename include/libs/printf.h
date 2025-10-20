/*
 * printf header file
 * user should implement __putc function
 */

#pragma once

#include <stdarg.h>
#include "libs/types.h"

usize   __putc(char c); // user's hook

isize   vprintf(const char *fmt, va_list ap);
isize   printf(const char *fmt, ...);