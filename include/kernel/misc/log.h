/*
 * logging functions.
 */

#ifndef _K_MISC_LOG_H
#define _K_MISC_LOG_H 1

#include "libs/color.h"
#include "kernel/misc/printk.h"
#include "kernel/arch/sbi.h"

#define COLOR_TRACE     COLOR_BOLD_BLACK
#define COLOR_INFO      COLOR_BOLD_CYAN
#define COLOR_NOTIFY    COLOR_BOLD_PURPLE
#define COLOR_WARN      COLOR_YELLOW
#define COLOR_PANIC     COLOR_BOLD_RED

#define trace(fmt, ...) \
    do { \
        printk(COLOR_TRACE "[TRACE|%s:%d]\t", __FILE__, __LINE__); \
        printk(fmt, ##__VA_ARGS__); \
        printk("\n" COLOR_RESET); \
    } while(0)

#define info(fmt, ...) \
    do { \
        printk(COLOR_INFO "[INFO|%s:%d]\t", __FILE__, __LINE__); \
        printk(fmt, ##__VA_ARGS__); \
        printk("\n" COLOR_RESET); \
    } while(0)

#define notify(fmt, ...) \
    do { \
        printk(COLOR_NOTIFY "[NOTIFY|%s:%d]\t", __FILE__, __LINE__); \
        printk(fmt, ##__VA_ARGS__); \
        printk("\n" COLOR_RESET); \
    } while(0)

#define warn(fmt, ...) \
    do { \
        printk(COLOR_WARN "[WARN|%s:%d]\t", __FILE__, __LINE__); \
        printk(fmt, ##__VA_ARGS__); \
        printk("\n" COLOR_RESET); \
    } while(0)

#define panic(fmt, ...) \
    do { \
        printk(COLOR_PANIC "[PANIC|%s:%d]\t", __FILE__, __LINE__); \
        printk(fmt, ##__VA_ARGS__); \
        printk("\n" COLOR_RESET); \
        sbi_shutdown(); \
    } while(0); \
    __builtin_unreachable(); \


#endif