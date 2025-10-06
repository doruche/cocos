#ifndef _K_MISC_PANIC_H
#define _K_MISC_PANIC_H 1

#include <stdbool.h>
#include "kernel/arch/sbi.h"
#include "kernel/misc/printk.h"
#include "types.h"

// void panic(const char *msg);

#ifndef PANIC_TEST
    #define panic(fmt, ...) \
        do { \
            printk("PANIC at %s:%d: ", __FILE__, __LINE__); \
            printk(fmt, ##__VA_ARGS__); \
            printk("\n"); \
            sbi_shutdown(); \
        } while(0)
#else
    #define panic(fmt, ...) \
        do { \
            printk("PANIC at %s:%d: ", __FILE__, __LINE__); \
            printk(fmt, ##__VA_ARGS__); \
            printk("\n"); \
        } while(0)
#endif

#define unreachable() \
    panic("unreachable code reached at %s:%d\n", __FILE__, __LINE__)

#define umimplemented() \
    panic("unimplemented code reached at %s:%d\n", __FILE__, __LINE__)

#define todo() \
    panic("todo at %s:%d\n", __FILE__, __LINE__)

#define assert(condition, msg) \
    do { \
        if(!(condition)) { \
            panic(msg); \
        } \
    } while(0)

#define assert_eq(x, y, msg) \
    do { \
        if((x) != (y)) { \
            panic(msg); \
        } \
    } while(0)

#define assert_ne(x, y, msg) \
    do { \
        if((x) == (y)) { \
            panic(msg); \
        } \
    } while(0)

#endif /* _K_MISC_PANIC_H */