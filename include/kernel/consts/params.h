/*
 * custom parameters about the operating system
 */

#pragma once

#include <libs/prelude.h>

#define BOOT_STACK_SIZE (8 * PAGE_SIZE)

#define USTACK_SIZE (8 * PAGE_SIZE) // 32KB user stack

#define KSTACK_SIZE (2 * PAGE_SIZE) // 8KB kernel stack per process

#define TASK_NAME_MAX_LEN 32

// max physical pages a task can alloc via sys_pm_alloc
// too rigid, but good enough for now (128 KB)
// optimize later with dynamic array (list is too heavyweight)
#define TASK_MAX_PHYS_PAGES 32