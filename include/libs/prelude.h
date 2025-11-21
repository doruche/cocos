#pragma once

#include <stdarg.h>

#define NULL ((void*)0)

#define TAG(name) 

#define __user      TAG(user)
#define __root      TAG(root)
#define __readonly  TAG(readonly)

#define __noreturn      __attribute__((noreturn))
#define __section(name) __attribute__((section(name)))
#define __maybe_unused  __attribute__((unused))
#define __aligned(x)   __attribute__((aligned(x)))

#define offset_of(type, member)  ((usize) &((type *)0)->member)
#define container_of(ptr, type, member) ({          \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offset_of(type,member) );})
#define array_size(arr) (sizeof(arr) / sizeof((arr)[0]))
#define sizeof_member(type, member) sizeof(((type *)0)->member)

#define swap(a, b) do { \
    typeof(a) __tmp = (a); \
    (a) = (b); \
    (b) = __tmp; \
} while (0)

#define align_up(size, align) \
    (((u64)(size) + (u64)(align) - 1) & ~((u64)(align) - 1))
#define align_down(size, align) \
    ((u64)(size) & ~((u64)(align) - 1))
#define is_aligned(size, align) \
    (bool)(((u64)(size) & ((u64)(align) - 1)) == 0)

#define loop while(1)

#define PAGE_SIZE   0x1000
#define PAGE_SHIFT  12
#define PAGE_MASK   (PAGE_SIZE - 1)

#define PGUP(addr) (((addr) + PAGE_MASK) & ~PAGE_MASK)
#define PGDOWN(addr) ((addr) & ~PAGE_MASK)

// convert page number to page address
#define PN2PA(ppn) ((ppn) << PAGE_SHIFT)
// convert page address to page number
#define PA2PN(pa)  ((pa) >> PAGE_SHIFT)

/// bit should be declared as bool
#define bit_traverse(bitmap, nbits, byte_cursor, bit_cursor) \
    for (usize byte_cursor = 0; byte_cursor < ((nbits) + 7) / 8; byte_cursor++) \
        for (usize bit_cursor = 0; \
            bit_cursor < 8 && (byte_cursor * 8 + bit_cursor) < (nbits) \
            ; bit_cursor++) \
        // body. byte and bit are valid here

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

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

typedef u64 paddr_t;
typedef u64 vaddr_t;
typedef u64 kaddr_t;
typedef u64 uaddr_t;
typedef u64 ppn_t;
typedef u64 vpn_t;
typedef u64 pte_t;

typedef isize result_t;
#define is_err(result) ((result) < 0)
#define OK          0  // Success
/* normal logic errors */
#define ERR_NOMEM   1  // Out of memory
#define ERR_INVAL   2  // Invalid argument
#define ERR_PERM    3  // Permission denied
#define ERR_NOENT   4  // No such entry
#define ERR_EXIST   5  // Entry already exists
#define ERR_FAULT   6  // Bad address
#define ERR_ABORT   7  // Operation aborted
#define ERR_MISSMATCH 8  // Entity mismatch
#define ERR_NOSPC   9  // No space left
#define ERR_MSG_TOOLONG 10 // Message too long
#define ERR_DEAD_TASK 11 // Destination task is dead
#define ERR_WOULD_BLOCK 12 // Ipc would block
#define ERR_DEV_BUSY 13 // Device busy
#define ERR_BUF_OVERFLOW 14 // Buffer overflow
#define ERR_UNKNOWN_REQ 15 // Unknown request
/* user exit reasons */
#define ERR_PAGEFAULT       42 // Page fault
#define ERR_KILLED          43 // Task killed
#define ERR_INVALID_SYSCALL 44 // Invalid syscall
#define ERR_PANIC           45 // Process panic
#define ERR_ACCESS_FAULT    46 // Access fault

static inline char*
strerr(isize err) {
    switch (err) {
        case OK:
            return "Success";
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
        case -ERR_ABORT:
            return "Operation aborted";
        case -ERR_MISSMATCH:
            return "Entity mismatch";
        case -ERR_NOSPC:
            return "No space left";
        case -ERR_MSG_TOOLONG:
            return "Message too long";
        case -ERR_DEAD_TASK:
            return "Destination task is dead";
        case -ERR_WOULD_BLOCK:
            return "Ipc would block";
        case -ERR_DEV_BUSY:
            return "Device busy";
        case -ERR_BUF_OVERFLOW:
            return "Buffer overflow";
        case -ERR_UNKNOWN_REQ:
            return "Unknown request";
        case -ERR_PAGEFAULT:
            return "Page fault";
        case -ERR_KILLED:
            return "Task killed";
        case -ERR_INVALID_SYSCALL:
            return "Invalid syscall";
        case -ERR_PANIC:
            return "Process panic";
        default:
            return "Unknown error";
    }
}

typedef usize tid_t;
#define TID_INVALID ((tid_t)-2)
/* -1 for TID_ANY (a.k.a. IPC_OPEN) */
#define TID_ANY     ((tid_t)-1)
#define TID_KERNEL  ((tid_t)0)
#define TID_PM      ((tid_t)1)

typedef struct _zombie_task_t {
    tid_t tid;
    result_t exit_code;
} zombie_task_t;

typedef u64 asid_t;
#define ASID_INVALID ((asid_t)-1)
#define ASID_NEW     ((asid_t)0)
typedef u64 vm_flags_t;
#define VM_READ  (1L << 0)
#define VM_WRITE (1L << 1)
#define VM_EXEC  (1L << 2)
#define VM_USER  (1L << 3)
// fake mapping, e.g. for guard page.
// note that when setting up fake mapping, it is necessary to set at least one PTE flag,
// on which we rely to detect fake mapping in page fault handler.
#define VM_FAKE  (1L << 5)
// anonymous mapping.
#define VM_ANON  (1L << 6)
#define PPN_ANON 0L

typedef u32 irq_t;

isize   vprintf(const char *fmt, va_list ap);
isize   printf(const char *fmt, ...);
void    printf_flush(void);

#define SYS_TASK_DESTROY 0
#define SYS_TASK_GETTID 1
#define SYS_DBG_PUTS    2
#define SYS_AS_GET      3
#define SYS_AS_MAP      4
#define SYS_AS_UNMAP    5
#define SYS_TASK_SPAWN  6
#define SYS_TASK_YIELD  8
#define SYS_IPC         9
#define SYS_NOTIFY      10
#define SYS_TASK_BLOCK  14
#define SYS_TASK_RESUME 15
#define SYS_AS_READ     18
#define SYS_AS_MEMCPY   19
#define SYS_TASK_EXIT   20
#define SYS_TASK_GETZOMBIE  21
#define SYS_AS_MEMSET   22
#define SYS_IRQ_LISTEN  23
#define SYS_IRQ_UNLISTEN    24
#define SYS_IRQ_ACK     25


#include <libs/log.h>
#include <libs/assert.h>
#include <libs/ipc.h>
#include <libs/string.h>
