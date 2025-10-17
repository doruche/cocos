/*
 * custom parameters about the operating system
 */

#pragma once

#include "kernel/arch/mm.h"

#define BOOT_STACK_SIZE (8 * PAGE_SIZE)

#define KERNEL_HEAP_SIZE (2 * PAGE_SIZE * PAGE_SIZE) // 2MB kernel heap

#define USTACK_SIZE (8 * PAGE_SIZE) // 32KB user stack

#define KSTACK_SIZE (2 * PAGE_SIZE) // 8KB kernel stack per process

