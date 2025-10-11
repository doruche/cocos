#include "kernel/mm/vm.h"
#include "kernel/arch/mm.h"
#include "kernel/mm/pm.h"
#include "libs/list.h"
#include "kernel/misc/assert.h"
#include "kernel/misc/log.h"

// to manage kernel and user vm spaces, we adopt a simple strategy:
// 1. kernel space is static, we map all the memory regions at once during boot
// 2. user space is copied from kernel space at initialization, and they are
//    then mapped on demand (page fault).

vm_space_t kernel_vms;

void kvms_init(bootinfo_t* bootinfo) {
    vm_init(&kernel_vms);
    // todo();
}

void
vm_init(vm_space_t* vms) {
    list_init(&vms->areas);
    ppn_t pgtbl_ppn = palloc();
    assert_ne(pgtbl_ppn, 0);
    vms->pgtbl = (pgtbl_t*)PPN2PA(pgtbl_ppn);
}

void
vm_destroy(vm_space_t* vms) {
    todo();
}

/// create a new vm area and map it
/// note that we do not grow/shrink areas for simplicity
void
vm_map(
    vm_space_t* vms,
    vpn_t vpn,
    ppn_t ppn,
    usize npages,
    enum vm_area_type type,
    vm_area_flags_t flags
) {
    assert(npages > 0);
    assert(type >= VM_RESERVED && type <= VM_MAPPED);

    // check for overlapping
    list_foreach(iter, &vms->areas) {
        vm_area_t* area = list_entry(iter, vm_area_t, list);
        if (!(vpn + npages <= area->start || vpn >= area->end)) {
            panic("vm_map: overlapping areas");
        }
    }

    // create new area
    
}