/*
 * useful macros
 */

#ifndef _LIBS_MACROS_H
#define _LIBS_MACROS_H 1

#include "libs/types.h"

#define offset_of(type, member)  ((usize) &((type *)0)->member)
#define container_of(ptr, type, member) ({          \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offset_of(type,member) );})
#define array_size(arr) (sizeof(arr) / sizeof((arr)[0]))

#define align_up(size, align) \
    (((u64)(size) + (u64)(align) - 1) & ~((u64)(align) - 1))
#define align_down(size, align) \
    ((u64)(size) & ~((u64)(align) - 1))
#define is_aligned(size, align) \
    (bool)(((u64)(size) & ((u64)(align) - 1)) == 0)

#define loop while(1)

/// bit should be declared as bool
#define bit_traverse(bitmap, nbits, byte_cursor, bit_cursor) \
    for (usize byte_cursor = 0; byte_cursor < ((nbits) + 7) / 8; byte_cursor++) \
        for (usize bit_cursor = 0; \
            bit_cursor < 8 && (byte_cursor * 8 + bit_cursor) < (nbits) \
            ; bit_cursor++) \
        // body. byte and bit are valid here

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define __noreturn      __attribute__((noreturn))
#define __section(name) __attribute__((section(name)))
#define __maybe_unused  __attribute__((unused))

#endif