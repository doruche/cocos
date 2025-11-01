/*
 * memory management
 */

#pragma once

#include "libs/prelude.h"

void* malloc(usize size);
void  free(void* ptr);
void* realloc(void* ptr, usize new_size);
void* calloc(usize num, usize size);