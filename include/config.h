/*
 * cocos operating system configurations
 */

#pragma once

#ifndef NCPU
    #define NCPU    1
#elif NCPU > 1
    #error "SMP is not supported yet"
#endif

#ifndef PAGE_SIZE
    #define PAGE_SIZE   0x1000
#endif

#define BOOT_STACK_SIZE (8 * PAGE_SIZE)

#define USTACK_SIZE (8 * PAGE_SIZE) // 32KB user stack

#define KSTACK_SIZE (2 * PAGE_SIZE) // 8KB kernel stack per process

#define SERIAL_BUF_MAX_LEN 128

#define NUM_CMD_ARGS_MAX 8

/* 64KB heap */
#define USER_HEAP_SIZE (1024 * 64)

#define PATH_MAX_LEN 64
#define FILE_NAME_MAX_LEN 8
#define FS_TYPE_MAX_LEN 16

/*
 * although our kernel supports infinite tasks on theory,
 * we limit the max number of tasks in user space for simplicity.
 * (why? can it really simplify anything? probably not much...
 * idk. just leave it as is for now.)
 */

#define MAX_TASK_NUM 128

#define MAX_FDS_PER_PROC 32

#define INIT_SERVERS \
    { "uart16550", "ns", "random", "idle", NULL }

#define INIT_APPS \
    { "shell", NULL }

