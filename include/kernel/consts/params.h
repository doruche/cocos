/*
 * custom parameters about the kernel
 */

#pragma once

#ifndef PAGE_SIZE
    #define PAGE_SIZE   0x1000
#endif

#ifndef NCPU
    #define NCPU    1
#elif NCPU > 1
    #error "SMP is not supported yet"
#endif

#define BOOT_STACK_SIZE (8 * PAGE_SIZE)

#define USTACK_SIZE (8 * PAGE_SIZE) // 32KB user stack

#define KSTACK_SIZE (2 * PAGE_SIZE) // 8KB kernel stack per process

#define TASK_NAME_MAX_LEN 32

// max physical pages a task can alloc via sys_pm_alloc
// too rigid, but good enough for now (128 KB)
// optimize later with dynamic array (list is too heavyweight)
#define TASK_MAX_PHYS_PAGES 32