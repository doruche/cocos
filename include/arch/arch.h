/*
    architecture related constants and macros.
*/

#ifndef _COMMON_ARCH_H
#define _COMMON_ARCH_H 1

#ifndef NCPU
    #define NCPU 1
#elif NCPU != 1
    #error "currently only support uniprocessor"
#endif

#endif