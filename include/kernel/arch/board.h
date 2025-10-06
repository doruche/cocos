/*
 * board specific definitions
 */

#ifndef _K_COMMON_ARCH_H
#define _K_COMMON_ARCH_H 1

#ifndef NCPU
    #define NCPU 1
#elif NCPU != 1
    #error "currently only support uniprocessor"
#endif

#endif