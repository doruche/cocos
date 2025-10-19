#pragma once

#define NULL ((void*)0)

#define TAG(name) 

#define __user      TAG(user)
#define __root      TAG(root)
#define __readonly  TAG(readonly)

#define __noreturn      __attribute__((noreturn))
#define __section(name) __attribute__((section(name)))
#define __maybe_unused  __attribute__((unused))

#ifndef __DEFONLY__

#include <stdbool.h>
typedef unsigned char       u8;
typedef signed char         i8;
typedef unsigned short      u16;
typedef signed short        i16;
typedef unsigned int        u32;
typedef signed int          i32;
typedef unsigned long long  u64;
typedef signed long long    i64;
typedef float               f32;
typedef double              f64;

typedef u64 usize;
typedef i64 isize;

// should migrate to other place later
typedef u64 paddr_t;
typedef u64 vaddr_t;
typedef u64 kaddr_t;
typedef u64 uaddr_t;
typedef u64 ppn_t;
typedef u64 vpn_t;

typedef usize tid_t;

#endif