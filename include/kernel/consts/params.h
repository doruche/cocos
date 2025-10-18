/*
 * custom parameters about the operating system
 */

#pragma once

#include "kernel/arch/mm.h"
#include "kernel/arch/board.h"

#define INTERVAL FREQUENCY / 10 // timer interrupt interval: 0.1s

#define BOOT_STACK_SIZE (8 * PAGE_SIZE)

#define KERNEL_HEAP_SIZE (2 * PAGE_SIZE * PAGE_SIZE) // 2MB kernel heap

#define USTACK_SIZE (8 * PAGE_SIZE) // 32KB user stack

#define KSTACK_SIZE (2 * PAGE_SIZE) // 8KB kernel stack per process

#define TASK_NAME_MAX_LEN 32

