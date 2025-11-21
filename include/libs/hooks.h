/*
 * hooks user of libcocos must implement.
 */

#pragma once

#include "libs/prelude.h"

#define hook_call(hook, ...) \
    __##hook(__VA_ARGS__)

#define __hook_impl TAG(hook_impl)

/* panic handling */
extern void __panic(const char* msg, ...);
extern void __panic_no_msg(void);

/*
 * printf
 * this implementation supports:
 * 1. %[l]<b|o|d|x>
 * 2. %p
 * 3. %c, %s
 * 4. %%
 * format specifiers.
 */
extern usize   __puts(const char* str);

/* dynamic memory allocation */
extern usize __objsize(void* ptr);
extern void* __malloc(usize size);
extern void  __free(void* ptr);