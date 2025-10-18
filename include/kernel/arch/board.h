/*
 * board specific definitions
 */

#pragma once

#ifndef NCPU
    #define NCPU 1
#elif NCPU != 1
    #error "currently only support uniprocessor"
#endif

#define FREQUENCY   10000000UL  // 10MHz

// actually i mean sbi.(x
#define BIOS_BASE   0x80000000UL

#define KERN_BASE   0x80200000 // do not use UL here cz we should include this in linker script
#define PHYSTOP     0x80000000UL + 128*1024*1024  // 128MB

// sv39
// reason for minus 1: avoid complexities with sign extension
#define VIRSTOP     (1UL << (39 - 1))

#define UART0           0x10000000UL
#define UART0_RANGE     0x1000UL
#define PLIC            0x0C000000UL
#define PLIC_RANGE      0x4000000UL

#define VIRTIO0         0x10001000UL  // virtio-blk
#define VIRTIO0_RANGE   0x1000UL
