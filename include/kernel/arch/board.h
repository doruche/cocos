/*
 * board specific definitions
 */

#pragma once

#ifndef NCPU
    #define NCPU 1
#elif NCPU != 1
    #error "currently only support uniprocessor"
#endif

// actually i mean sbi.(x
#define BIOS_BASE   0x80000000

#define KERN_BASE   0x80200000
#define PHYSTOP     0x80000000 + 128*1024*1024  // 128MB

// sv39
// reason for minus 1: avoid complexities with sign extension
#define VIRSTOP     (1UL << (39 - 1))

#define UART0           0x10000000
#define UART0_RANGE     0x1000
#define PLIC            0x0C000000
#define PLIC_RANGE      0x4000000

#define VIRTIO0         0x10001000  // virtio-blk
#define VIRTIO0_RANGE   0x1000
