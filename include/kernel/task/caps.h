/*
 * task capabilities
 */

#pragma once

#include "libs/types.h"

typedef u64 cap_t;

// delegated to pm at first and distributed later.
#define CAP_GODMODE ((cap_t)-1)
// no capability. for normal tasks.
#define CAP_NONE    ((cap_t)0)
// access to physical memory allocation/deallocation
#define CAP_DRIVER  ((cap_t)1)
// access to vm management (mmap/munmap/protect/etc)
#define CAP_VM      ((cap_t)2)
// access to task management (spawn/kill/yield/etc)
#define CAP_SYS    ((cap_t)3)