#include "kernel/mm/vm.h"
#include "kernel/arch/mm.h"
#include "kernel/mm/pm.h"
#include "kernel/mm/slab.h"
#include "libs/list.h"
#include "kernel/misc/assert.h"
#include "kernel/misc/log.h"
#include "kernel/mm/kmalloc.h"
#include "libs/string.h"
#include "libs/macros.h"


// to manage kernel and user vm spaces, we adopt a simple strategy:
// 1. kernel space is static, we map all the memory regions at once during boot
// 2. user space is copied from kernel space at initialization, and they are
//    then mapped on demand (page fault).

vm_space_t kernel_vms;

kmem_cache_t area_cache;

// each task's vms field is just a pointer to one of these,
// thus we can easily manage shared memory spaces.
// list_head(vm_spaces);

void kvms_init(bootinfo_t* bootinfo) {
    area_cache = kmem_cache_create(sizeof(vm_area_t));

    vm_init(&kernel_vms);

    // map all needed regions
    for (usize i = 0; i < NMEMZONE_MAX; i++) {
        // we do not map device memory here,
        // as they will be accessed by driver in user space.
        memzone_t* zone = &bootinfo->zones[i];
        vm_area_flags_t flags = 0;
        switch (zone->type) {
            case MEMZONE_K_TEXT:
                flags = VM_READ | VM_EXEC;
                break;
            case MEMZONE_K_RODATA:
                flags = VM_READ;
                break;
            case MEMZONE_K_DATA:
            case MEMZONE_K_BSS:
            case MEMZONE_FREE:
                flags = VM_READ | VM_WRITE;
                break;
            case MEMZONE_DEV:
                // device memory, we do not map it here.
                info("found device memory zone [%lx, %lx), skip mapping",
                    zone->start, zone->end);
                continue;
            case MEMZONE_NONE:
                goto done;
            default:
                unreachable();
        }
        vm_map(
            &kernel_vms,
            PA2PN(zone->start),
            PA2PN(zone->start),
            (zone->end - zone->start) / PAGE_SIZE,
            VM_RESERVED,
            flags
        );
    }
done:
    flush_tlb();
    vm_activate(&kernel_vms);
}

void
vm_init(vm_space_t* vms) {
    list_init(&vms->areas);
    ppn_t pgtbl_ppn = palloc();
    assert_ne(pgtbl_ppn, 0);
    vms->pgtbl = (pgtbl_t*)PN2PA(pgtbl_ppn);
    pgtbl_init(vms->pgtbl);
}

static void
vm_area_destroy(vm_space_t* vms, vm_area_t* area) {
    trace("destroying vm area [%lx, %lx) type=%d flags=%lx",
        PN2PA(area->start), PN2PA(area->end), area->type, area->flags);
    
    switch (area->type) {
        case VM_RESERVED:
            vm_unmap(vms, area->start, area->end - area->start, false);
            break;
        case VM_ALLOCATED:
            vm_unmap(vms, area->start, area->end - area->start, true);
            break;
        default:
            unreachable();
    }

    // free area struct
    // these are currently handled in vm_unmap()
    // we shall refactor this ugly design later.
    // list_remove(&vms->areas, &area->node);
    // kmem_cache_free(&area_cache, area);
}

void
vm_destroy(vm_space_t* vms) {
    // unmap all areas
    list_foreach_safe(iter, &vms->areas, next) {
        vm_area_t* area = list_entry(iter, vm_area_t, node);
        vm_area_destroy(vms, area);
    }

    assert(vms->areas.next == &vms->areas); // all areas should be destroyed
    pgtbl_destroy(vms->pgtbl); // and all mappings should be removed
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
    assert(type >= VM_RESERVED && type <= VM_ALLOCATED);

    // check for overlapping
    list_foreach(iter, &vms->areas) {
        vm_area_t* area = list_entry(iter, vm_area_t, node);
        // though whether two areas overlap should be judged by their bitmaps,
        // but that would always be a bug in our current design,
        // so we just check their ranges here.
        if (!(vpn + npages <= area->start || vpn >= area->end)) {
            panic("vm_map: overlapping areas");
        }
    }

    // create new area
    vm_area_t* area = kmem_cache_alloc(&area_cache);
    assert_ne(area, NULL);
    area->start = vpn;
    area->end = vpn + npages;
    area->type = type;
    area->flags = flags;

    list_push_back(&vms->areas, &area->node);

    // map new area
    for (usize i = 0; i < npages; i++) {
        pgtbl_map(
            vms->pgtbl,
            vpn + i,
            ppn + i,
            pte_vmflag2archflag(flags)
        );
    }
}

static bool
vpn_in_area(vpn_t vpn, vm_area_t* area) {
    if (vpn < area->start || vpn >= area->end) {
        return false;
    }
    return true;
}

// unmap a region within an area.
// when unmapping, we check if we should split.
// we do not merge areas for simplicity. besides, it's
// too complicated to check whether two areas can be merged. (e.g. type and flags)
// NOTE areas list manipulations are also done here!!!
// do not call vm_area_destroy(), which will cause a recursion!!!
static void
vm_unmap_in_area(vm_space_t* vms, vpn_t vpn, usize npages, bool free_pages) {
    assert(npages > 0);

    // find the area
    vm_area_t* area = NULL;
    list_foreach(iter, &vms->areas) {
        vm_area_t* a = list_entry(iter, vm_area_t, node);
        if (vpn_in_area(vpn, a)) {
            area = a;
            break;
        }
    }
    if (vpn + npages > area->end) {
        panic("vm_unmap: unmapping beyond area end");
    }
    if (area == NULL) {
        panic("vm_unmap: area not found");
    }

    vpn_t unmap_end = vpn + npages;

    trace("vm_unmap: unmapping [%lx, %lx) from area [%lx, %lx) type=%d flags=%lx",
        PN2PA(vpn), PN2PA(unmap_end), PN2PA(area->start), PN2PA(area->end), area->type, area->flags);
 
    // 4 cases:
    // 1. area->start == vpn && area->end == unmap_end
    // 2. area->start == vpn && area->end > unmap_end
    // 3. area->start < vpn && area->end == unmap_end
    // 4. area->start < vpn && area->end > unmap_end
    if (area->start == vpn && area->end == unmap_end) {
        // case 1, just destroy the area
        for (usize i = 0; i < npages; i++) {
            // we can't assume the allocated pages are continuous
            ppn_t ppn = vm_translate(vms, vpn + i);
            pgtbl_unmap(vms->pgtbl, vpn + i);
            if (free_pages) {
                pfree(ppn);
            }
        }
        list_remove(&vms->areas, &area->node);
        kmem_cache_free(&area_cache, area);
    } else if (area->start == vpn && area->end > unmap_end) {
        // case 2, shrink from the start
        for (usize i = 0; i < npages; i++) {
            ppn_t ppn = vm_translate(vms, vpn + i);
            pgtbl_unmap(vms->pgtbl, vpn + i);
            if (free_pages) {
                pfree(ppn);
            }
        }
        area->start = unmap_end;
    } else if (area->start < vpn && area->end == unmap_end) {
        // case 3, shrink from the end
        for (usize i = 0; i < npages; i++) {
            ppn_t ppn = vm_translate(vms, area->end - 1 - i);
            pgtbl_unmap(vms->pgtbl, area->end - 1 - i);
            if (free_pages) {
                pfree(ppn);
            }
        }
        area->end = vpn;
    } else {
        // case 4, split into two areas
        for (usize i = 0; i < npages; i++) {
            ppn_t ppn = vm_translate(vms, vpn + i);
            pgtbl_unmap(vms->pgtbl, vpn + i);
            if (free_pages) {
                pfree(ppn);
            }
        }
        
        vm_area_t* left = kmem_cache_alloc(&area_cache);
        assert_ne(left, NULL);
        left->start = area->start;
        left->end = vpn;
        left->type = area->type;
        left->flags = area->flags;
        
        vm_area_t* right = kmem_cache_alloc(&area_cache);
        assert_ne(right, NULL);
        right->start = unmap_end;
        right->end = area->end;
        right->type = area->type;
        right->flags = area->flags;

        // remove old area
        list_remove(&vms->areas, &area->node);
        kmem_cache_free(&area_cache, area);
        // insert new areas
        list_push_back(&vms->areas, &left->node);
        list_push_back(&vms->areas, &right->node);
    }
}

// this function can unmap across multiple areas
void
vm_unmap(vm_space_t* vms, vpn_t vpn, usize npages, bool free_pages) {
    assert(npages > 0);

    while (npages > 0) {
        // find the area
        vm_area_t* area = NULL;
        list_foreach(iter, &vms->areas) {
            vm_area_t* a = list_entry(iter, vm_area_t, node);
            if (vpn_in_area(vpn, a)) {
                area = a;
                break;
            }
        }
        if (area == NULL) {
            panic("vm_unmap: area not found");
        }

        // unmap as much as we can in this area
        usize to_unmap = min(npages, area->end - vpn);
        vm_unmap_in_area(vms, vpn, to_unmap, free_pages);

        vpn += to_unmap;
        npages -= to_unmap;
    }
}

ppn_t
vm_translate(vm_space_t* vms, vpn_t vpn) {
    return pgtbl_lookup(vms->pgtbl, vpn);
}

void
vm_activate(vm_space_t* vms) {
    // set the root page table
    pgtbl_activate(vms->pgtbl);
}

#ifdef VM_DEBUG

void
vm_dump(vm_space_t* vms) {
    trace("vm space dump:");
    list_foreach(iter, &vms->areas) {
        vm_area_t* area = list_entry(iter, vm_area_t, node);
        trace("  area [%lx, %lx) type=%d flags=%lx",
            area->start, area->end, area->type, area->flags);
        for (usize i = 0; i < area->end - area->start; i++) {
            if (area->bitmap[i]) {
                ppn_t ppn = vm_translate(vms, area->start + i);
                assert_ne(ppn, 0);
                trace("    page %lx -> %lx", area->start + i, ppn);
            }
        }
    }
}

#endif