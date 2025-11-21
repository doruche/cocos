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

#define TASK_NAME_MAX_LEN 32

#define SERIAL_BUF_MAX_LEN 128

#define NUM_CMD_ARGS_MAX 8

#define INIT_SERVERS \
    { "uart16550", "random", "echo", "idle", NULL }

#define INIT_APPS \
    { "shell", NULL }

