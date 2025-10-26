/*
 * panic handler hook
 * kernel/uspace must define __panic macro before linking
 * general libs.
 */

#pragma once

/*
 * panic(msg, __VA_ARGS__)
 */

extern void __panic(const char* msg, ...);
extern void __panic_no_msg(void);