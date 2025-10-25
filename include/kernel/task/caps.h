/*
 * task capabilities
 * todo. currently unused.
 */

#pragma once

#include "libs/types.h"

typedef u64 cap_t;

// delegated to pm at first and distributed later.
#define CAP_GODMODE ((cap_t)-1)
// no capability. for normal tasks.
#define CAP_IRQ     ((cap_t)(1 << 0))
// task management access
#define CAP_SYSTEM  ((cap_t)(1 << 1))
// memory management access
#define CAP_MM      ((cap_t)(1 << 2))
// port creation
#define CAP_COMM    ((cap_t)(1 << 4))
// kernel debugging
#define CAP_DBG     ((cap_t)(1 << 5))
// no capability. for most common tasks.
#define CAP_NONE    ((cap_t)0)