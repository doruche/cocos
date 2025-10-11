/*
 * virtual memory management
 */
#ifndef _K_MM_VM_H
#define _K_MM_VM_H 1

#ifndef __DEFONLY__

#include "libs/types.h"
#include "libs/list.h"
#include "kernel/arch/mm.h"

enum vm_area_type {
    VM_RESERVED = 0, // mapped but not allocated (e.g. MMIO regions)
    VM_ALLOCED = 1, // allocated but not mapped
    VM_MAPPED = 2, // allocated and mapped
    // we use these types to indicate how we tackle of them.
};

typedef u64 vm_area_flags_t;

#define VM_READ  (1L << 0)
#define VM_WRITE (1L << 1)
#define VM_EXEC  (1L << 2)
#define VM_USER  (1L << 3)

typedef struct _vm_area_t {
    // [start, end)
    vpn_t start;
    vpn_t end;
    enum vm_area_type type;
    list_elem_t list;
} vm_area_t;

typedef struct _vm_space_t {
    list_t areas; // list of vm_area_t
    pgtbl_t* pgtbl;
} vm_space_t;


// currently we do not do any error detection / recovery for simplicity
void        vm_init(vm_space_t* vms);
void        vm_destroy(vm_space_t* vms);
void        vm_map(vm_space_t* vms, vpn_t vpn, ppn_t ppn, usize npages, enum vm_area_type type, vm_area_flags_t flags);
void        vm_unmap(vm_space_t* vms, vpn_t vpn, usize npages);
paddr_t     vm_translate(vm_space_t* vms, vpn_t vpn);

void        vm_area_dump(vm_space_t* vms);

#include "kernel/boot.h"

void        kvms_init(bootinfo_t* bootinfo);

#endif

#endif