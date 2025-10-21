/*
 * virtual memory management
 */
#pragma once

#include "libs/types.h"
#include "libs/list.h"
#include "kernel/arch/mm.h"
#include "kernel/boot.h"

enum vm_area_type {
    VM_RESERVED = 0, // mapped but not allocated (e.g. MMIO regions)
    VM_ALLOCATED,   // allocated and mapped. come from physical memory allocator (free memory)
};

typedef u64 vm_area_flags_t;
#define VM_READ  (1L << 0)
#define VM_WRITE (1L << 1)
#define VM_EXEC  (1L << 2)
#define VM_USER  (1L << 3)
// fake mapping, e.g. for guard page. must be used with VM_RESERVED
// note that when setting up fake mapping, it is necessary to set at least one PTE flag,
// on which we rely to detect fake mapping in page fault handler.
#define VM_FAKE  (1L << 5)

typedef struct _vm_area_t {
    // [start, end)
    vpn_t start;
    vpn_t end;
    ppn_t sppn; // used when releasing memory back to pm
    enum vm_area_type type;
    vm_area_flags_t flags;
    list_elem_t node; // in vm_space_t's areas list
    // bool *bitmap; // for tracking allocated pages in this area, allocated dinamically
} vm_area_t;

typedef struct _vm_space_t {
    list_t areas; // list of vm_area_t
    pgtbl_t* pgtbl;
} vm_space_t;


// currently we do not do any error detection / recovery for simplicity
void        vm_init(vm_space_t* vms);
void        vm_destroy(vm_space_t* vms);
void        vm_map(
    vm_space_t* vms, 
    vpn_t vpn, 
    ppn_t ppn,
#define VM_FAKE_PPN 0 // used with VM_FAKE areas. e.g. guard page
    usize npages,
    enum vm_area_type type, 
    vm_area_flags_t flags
);
void        vm_unmap(vm_space_t* vms, vpn_t vpn, usize npages);
ppn_t       vm_translate(vm_space_t* vms, vpn_t vpn);
void        vm_activate(vm_space_t* vms);
// void        vm_copy_mappings(vm_space_t* dst, vm_space_t* src);

void        kvms_init(bootinfo_t* bootinfo);
void        kvms_derive(vm_space_t* vms);

void        vm_dump(vm_space_t* vms);