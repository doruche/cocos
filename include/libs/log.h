/*
 * logging functions.
 */

#pragma once

#include "libs/color.h"
#include "libs/hooks.h"

#ifndef LOG
    #define LOG TRACE
#endif

#ifndef NAME
    #define NAME ""
#endif

#define TRACE 3U
#define INFO 2U
#define NOTIFY 1U
#define WARN 0U

#define COLOR_TRACE     COLOR_BOLD_BLACK
#define COLOR_INFO      COLOR_BOLD_CYAN
#define COLOR_NOTIFY    COLOR_BOLD_PURPLE
#define COLOR_WARN      COLOR_YELLOW
#define COLOR_PANIC     COLOR_BOLD_RED

#define trace(fmt, ...) \
    do { \
        if (LOG < TRACE) break; \
        printf(COLOR_TRACE "[TRACE|" NAME "%s:%d]\t", __FILE__, __LINE__); \
        printf(fmt, ##__VA_ARGS__); \
        printf("\n" COLOR_RESET); \
    } while(0)

#define info(fmt, ...) \
    do { \
        if (LOG < INFO) break; \
        printf(COLOR_INFO "[INFO|" NAME "%s:%d]\t", __FILE__, __LINE__); \
        printf(fmt, ##__VA_ARGS__); \
        printf("\n" COLOR_RESET); \
    } while(0)

#define notify(fmt, ...) \
    do { \
        if (LOG < NOTIFY) break; \
        printf(COLOR_NOTIFY "[NOTIFY|" NAME "%s:%d]\t", __FILE__, __LINE__); \
        printf(fmt, ##__VA_ARGS__); \
        printf("\n" COLOR_RESET); \
    } while(0)

#define warn(fmt, ...) \
    do { \
        if (LOG < WARN) break; \
        printf(COLOR_WARN "[WARN|" NAME "%s:%d]\t", __FILE__, __LINE__); \
        printf(fmt, ##__VA_ARGS__); \
        printf("\n" COLOR_RESET); \
    } while(0)

#define panic(fmt, ...) \
    do { \
        printf(COLOR_PANIC "[PANIC|" NAME "%s:%d]\t", __FILE__, __LINE__); \
        printf(fmt, ##__VA_ARGS__); \
        printf("\n" COLOR_RESET); \
        __panic_no_msg(); \
    } while(0); \
    __builtin_unreachable(); 
