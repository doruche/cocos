#ifndef _K_MISC_ASSERT_H
#define _K_MISC_ASSERT_H 1

#include "kernel/misc/log.h"

#define unreachable() \
    panic("unreachable code reached.\n");

#define unimplemented() \
    panic("unimplemented code reached.\n");

#define todo() \
    panic("todo reached.\n");

#define assert(condition) \
    do { \
        if (!(condition)) { \
            panic("Assertion failed '%s': " \
                , #condition); \
        } \
    } while(0)

/*
 * Note that following assert macros treat x and y as integers.
 */

#define assert_eq(x, y) \
    do { \
        typeof(x) _x = (x); \
        typeof(y) _y = (y); \
        if(_x != _y) { \
            panic("Assertion failed '%s == %s': " \
                "\n\t left: %d" \
                "\n\tright: %d" \
                , #x, #y, _x, _y); \
        } \
    } while(0)

#define assert_ne(x, y) \
    do { \
        typeof(x) _x = (x); \
        typeof(y) _y = (y); \
        if(_x == _y) { \
            panic("Assertion failed '%s != %s': " \
                "\n\t left: %d" \
                "\n\tright: %d" \
                , #x, #y, _x, _y); \
        } \
    } while(0)

#endif