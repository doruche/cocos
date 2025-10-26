/*
 * printf header file
 * user should implement __puts function
 * this implementation supports:
 * 1. %[l]<b|o|d|x>
 * 2. %p
 * 3. %c, %s
 * 4. %%
 * format specifiers.
 */

#pragma once

#include <stdarg.h>
#include "libs/prelude.h"

extern usize   __puts(const char* str);

isize   vprintf(const char *fmt, va_list ap);
isize   printf(const char *fmt, ...);
void    flush(void);