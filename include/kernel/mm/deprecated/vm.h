/*
 * virtual memory management
 */
#pragma once

#include "libs/types.h"
#include "libs/list.h"
#include "kernel/arch/mm.h"
#include "kernel/boot.h"

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
void        vm_activate(vm_space_t* vms);
bool        vm_is_mapped(vm_space_t* vms, vpn_t vpn);
isize       vm_grant(
    vm_space_t* dst,
    vm_space_t* src,
    vpn_t from,
    vpn_t to,
    vm_area_flags_t flags
);

void        kvms_init(bootinfo_t* bootinfo);
void        kvms_derive(vm_space_t* vms);

void        vm_dump(vm_space_t* vms);