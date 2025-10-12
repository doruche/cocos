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
    (((size) + (align) - 1) & ~((align) - 1))

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#endif