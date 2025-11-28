/*
 * handle management utilities 
 */
#pragma once
#include <libs/prelude.h>
#include <libs/list.h>

/*
 * currently we adopt simple guid-based handles,
 * which means if one process can access a handle
 * if it knows the guid.
 * we may refine this later to a tuple-based handle:
 * <pid, guid>
 */

typedef u64 handle_t;
#define HANDLE_INVALID 0
