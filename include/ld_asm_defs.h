/*
 * exported definitions for assembly & linker scripts
 */

#pragma once

#ifndef KERN_BASE
    #define KERN_BASE   0x80000000
#endif

#define USER_BASE   0x12000000

#define PAGE_SIZE   0x1000

#define BOOT_STACK_SIZE (8 * PAGE_SIZE)

#ifndef NCPU
    #define NCPU    1
#elif NCPU > 1
    #error "SMP is not supported yet"
#endif