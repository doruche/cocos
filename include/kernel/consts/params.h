/*
 * custom parameters about the operating system
 */

#ifndef _K_COMMON_SIZE_H
#define _K_COMMON_SIZE_H 1

#include "kernel/arch/mm.h"

#define BOOT_STACK_SIZE (8 * PAGE_SIZE)

#define KERNEL_HEAP_SIZE (2 * PAGE_SIZE * PAGE_SIZE) // 2MB kernel heap

#endif