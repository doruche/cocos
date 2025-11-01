/*
 * flexible memory allocator based on slab allocator
 */
#pragma once

#include "libs/prelude.h"

void    kmalloc_init();
void*   kmalloc(usize size);
void    kfree(void* ptr);

usize   kmalloc_objsize(void* ptr);
