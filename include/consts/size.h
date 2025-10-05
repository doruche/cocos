/*
    constants about memory size and alignment.
*/

#ifndef _COMMON_SIZE_H
#define _COMMON_SIZE_H 1

#define PAGE_SIZE    0x1000
#define PAGE_SHIFT   12
#define PAGE_MASK    (PAGE_SIZE - 1)

#define BOOT_STACK_SIZE (8 * PAGE_SIZE)

#endif