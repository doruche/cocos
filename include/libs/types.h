#pragma once

#define NULL ((void*)0)

#define TAG(name) 

#define __user      TAG(user)
#define __root      TAG(root)
#define __readonly  TAG(readonly)

#define __noreturn      __attribute__((noreturn))
#define __section(name) __attribute__((section(name)))
#define __maybe_unused  __attribute__((unused))

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

typedef u64 vm_flags_t;
#define VM_READ  (1L << 0)
#define VM_WRITE (1L << 1)
#define VM_EXEC  (1L << 2)
#define VM_USER  (1L << 3)
// fake mapping, e.g. for guard page. must be used with VM_RESERVED
// note that when setting up fake mapping, it is necessary to set at least one PTE flag,
// on which we rely to detect fake mapping in page fault handler.
#define VM_FAKE  (1L << 5)

typedef struct _pm_access_params_t {
    tid_t tid;
    ppn_t ppn;
    vpn_t vpn;
    usize npages;
    bool write;
} pm_access_params_t;

#define ERR_NOMEM   1  // Out of memory
#define ERR_INVAL   2  // Invalid argument
#define ERR_PERM    3  // Permission denied
#define ERR_NOENT   4  // No such entry
#define ERR_EXIST   5  // Entry already exists
#define ERR_FAULT   6  // Bad address

static inline char*
strerr(isize err) {
    switch (err) {
        case -ERR_NOMEM:
            return "Out of memory";
        case -ERR_INVAL:
            return "Invalid argument";
        case -ERR_PERM:
            return "Permission denied";
        case -ERR_NOENT:
            return "No such entry";
        case -ERR_EXIST:
            return "Entry already exists";
        case -ERR_FAULT:
            return "Bad address";
        default:
            return "Unknown error";
    }
}