#pragma once

#include "kernel/misc/log.h"
#include "libs/types.h"

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


#define unwrap_err(x) ({ \
        isize _ret = (isize)(x); \
        do { \
        if (_ret < 0) { \
            panic("Assertion failed '(%s) >= 0': " \
                "\nreturn code: %d (%s)" \
                , #x, _ret, strerr(_ret)); \
        } } while(0); _ret; })

#define unwrap_null(x) ({ \
        typeof(x) _ret = (x); \
        do { \
        if (_ret == NULL) { \
            panic("Assertion failed '(%s) != NULL'\n", #x); \
        } } while(0); _ret; })
