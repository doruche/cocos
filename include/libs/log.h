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

#define pr_trace(fmt, ...) \
    do { \
        if (LOG < TRACE) break; \
        printf(COLOR_TRACE "[TRACE|" NAME "%s:%d]\t" COLOR_RESET, __FILE__, __LINE__); \
        printf(COLOR_TRACE fmt COLOR_RESET, ##__VA_ARGS__); \
        printf("\n"); \
    } while(0)

#define pr_info(fmt, ...) \
    do { \
        if (LOG < INFO) break; \
        printf(COLOR_INFO "[INFO|" NAME "%s:%d]\t" COLOR_RESET, __FILE__, __LINE__); \
        printf(COLOR_INFO fmt COLOR_RESET, ##__VA_ARGS__); \
        printf("\n"); \
    } while(0)

#define pr_notify(fmt, ...) \
    do { \
        if (LOG < NOTIFY) break; \
        printf(COLOR_NOTIFY "[NOTIFY|" NAME "%s:%d]\t" COLOR_RESET, __FILE__, __LINE__); \
        printf(COLOR_NOTIFY fmt COLOR_RESET, ##__VA_ARGS__); \
        printf("\n"); \
    } while(0)

#define pr_warn(fmt, ...) \
    do { \
        if (LOG < WARN) break; \
        printf(COLOR_WARN "[WARN|" NAME "%s:%d]\t" COLOR_RESET, __FILE__, __LINE__); \
        printf(COLOR_WARN fmt COLOR_RESET, ##__VA_ARGS__); \
        printf("\n"); \
    } while(0)

#define panic(fmt, ...) \
    do { \
        printf(COLOR_PANIC "[PANIC|" NAME "%s:%d]\t" COLOR_RESET, __FILE__, __LINE__); \
        printf(COLOR_PANIC fmt COLOR_RESET, ##__VA_ARGS__); \
        printf("\n"); \
        __panic_no_msg(); \
    } while(0); \
    __builtin_unreachable(); 
