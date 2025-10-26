/*
 * flexible memory allocator based on slab allocator
 */
#ifndef _K_MM_KMALLOC_H
#define _K_MM_KMALLOC_H 1

#ifndef __DEFONLY__

#include "libs/prelude.h"


void    kmalloc_init();
void*   kmalloc(usize size);
void    kfree(void* ptr);


#endif

#endif