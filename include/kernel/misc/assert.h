#pragma once

#include "kernel/misc/log.h"
#include "libs/errno.h"

#define unreachable() \
    panic("unreachable code reached.\n");

#define unimplemented() \
    panic("unimplemented code reached.\n");

#define todo() \
    panic("todo reached.\n");

#define assert(condition) \
    do { \
        if (!(condition)) { \
            panic("Assertion failed '%s'" \
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
            panic("Assertion failed '(%s) == (%s)': " \
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
            panic("Assertion failed '(%s) != (%s)': " \
                "\n\t left: %d" \
                "\n\tright: %d" \
                , #x, #y, _x, _y); \
        } \
    } while(0)


#define unwrap(x) ({ \
        isize _ret = (isize)(x); \
        do { \
        if (_ret < 0) { \
            panic("Assertion failed '(%s) >= 0': " \
                "\nreturn code: %d (%s)" \
                , #x, _ret, (_ret == -ENOMEM ? "Out of memory" : \
                            _ret == -EINVAL ? "Invalid argument" : \
                            _ret == -EBUSY  ? "Device or resource busy" : "Unknown error")); \
        } } while(0); _ret; })
