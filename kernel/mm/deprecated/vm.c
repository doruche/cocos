#include "kernel/mm/deprecated/vm.h"
#include "kernel/arch/mm.h"
#include "kernel/mm/pm.h"
#include "kernel/mm/slab.h"
#include "libs/list.h"
#include "libs/assert.h"
#include "libs/log.h"
#include "kernel/mm/kmalloc.h"
#include "libs/string.h"
#include "libs/macros.h"


// to manage kernel and user vm spaces, we adopt a simple strategy:
// 1. kernel space is static, we map all the memory regions at once during boot
// 2. user space is cloned from kernel space at initialization,
//    then mapped on demand during runtime.

vm_space_t kernel_vms;
kmem_cache_t area_cache;

void kvms_init(bootinfo_t* bootinfo) {
    kmem_cache_create(&area_cache, "vm_area_cache", sizeof(vm_area_t));

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
        if (zone->start == zone->end) {
            notify("skipping empty memory zone %d type %d", i, zone->type);
            continue;
        }
        vm_map(
            &kernel_vms,
            PA2PN(zone->start),
            PA2PN(zone->start),
            (zone->end - zone->start) / PAGE_SIZE,
            VM_RESERVED,
            flags
        );
        info("mapped kernel memory zone [%lx, %lx) flags=%c%c%c",
            zone->start, zone->end,
            (flags & VM_READ) ? 'r' : '-',
            (flags & VM_WRITE) ? 'w' : '-',
            (flags & VM_EXEC) ? 'x' : '-'
        );
    }
done:
    // note that we're still in booting stage (we're on boot_stack right now).
    // we'll switch to scheduler context just before running user tasks,
    // when we will use kernel_vms again for mapping TRAMPOLINE and scheduler kstack.

    flush_tlb();
    vm_activate(&kernel_vms);
}

void
vm_init(vm_space_t* vms) {
    list_init(&vms->areas);
    ppn_t pgtbl_ppn = unwrap_err(pm_alloc());
    vms->pgtbl = (pgtbl_t*)PN2PA(pgtbl_ppn);
    pgtbl_init(vms->pgtbl);
}


void
vm_destroy(vm_space_t* vms) {
    // unmap all areas
    list_foreach_safe(iter, &vms->areas, next) {
        vm_area_t* area = list_entry(iter, vm_area_t, node);
        usize npages = area->end - area->start;
        notify("vm_destroy: unmapping area [%lx, %lx) npages %ld",
            PN2PA(area->start), PN2PA(area->end), npages);
        vm_unmap(vms, area->start, npages);
    }

    assert(vms->areas.next == &vms->areas); // all areas should be destroyed
    notify("free pages before destroying pgtbl: %ld", pm_count_free()); 
    pgtbl_destroy(vms->pgtbl); // and all mappings should be removed
    notify("free pages after destroying pgtbl: %ld", pm_count_free());
}

/// create a new vm area and map it
void
vm_map(
    vm_space_t* vms,
    vpn_t vpn,
    ppn_t ppn,
    usize npages,
    enum vm_area_type type,
    vm_area_flags_t flags
) {
    if (npages == 0) {
        warn("vm_map: mapping zero pages at vpn %lx", PN2PA(vpn));
        return;
    }

    assert(type == VM_RESERVED || type == VM_ALLOCATED);
    if (flags & VM_FAKE) {
        assert(type == VM_RESERVED); // fake mappings can only be reserved
    }
    // check for overlapping
    list_foreach(iter, &vms->areas) {
        vm_area_t* area = list_entry(iter, vm_area_t, node);
        if (!(vpn + npages <= area->start || vpn >= area->end)) {
            panic("vm_map: overlapping areas when mapping [%lx, %lx) with existing area [%lx, %lx)",
                PN2PA(vpn), PN2PA(vpn + npages), PN2PA(area->start), PN2PA(area->end));
        }
    }

    // create new area
    vm_area_t* area = kmem_cache_alloc(&area_cache);
    assert_ne(area, NULL);
    area->start = vpn;
    area->end = vpn + npages;
    area->sppn = ppn;
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

static void
pgtbl_unmap_range(pgtbl_t* pgtbl, vpn_t svpn, usize npages) {
    for (usize i = 0; i < npages; i++) {
        pgtbl_unmap(pgtbl, svpn + i);
    }
}

// NOTE we do not support unmapping across multiple areas for simplicity
// but unmapping part of an area is supported,
// which will lead to a split of that area.
// this method also handles areas' list management.
static void
vm_unmap_inner(
    vm_space_t* vms, 
    vpn_t vpn, 
    usize npages,
    // the reason for this weird parameter is to avoid double free.
    // basically, it's just for vm_grant, which call this function with free_allocated = false.
    bool free_allocated
) {
    vm_area_t* area = NULL;
    list_foreach(iter, &vms->areas) {
        vm_area_t* a = list_entry(iter, vm_area_t, node);
        if (vpn_in_area(vpn, a)) {
            area = a;
            break;
        }
    }
    if (area == NULL) {
        panic("vm_unmap: no area contains vpn %lx", PN2PA(vpn));
    } 

    if (vpn + npages > area->end) {
        panic("vm_unmap: unmapping [%lx, %lx) exceeds area [%lx, %lx)",
            PN2PA(vpn), PN2PA(vpn + npages),
            PN2PA(area->start), PN2PA(area->end)
        );
    }

    bool free_pages = (area->type == VM_ALLOCATED) && free_allocated;

    // 4 cases:
    // 1. [vpn, vpn + npages) == [area->start, area->end)
    // 2. [vpn, vpn + npages) == [area->start, X), X < area->end
    // 3. [vpn, vpn + npages) == [X, area->end), X > area->start
    // 4. [vpn, vpn + npages) == [X, Y), area->start < X < Y < area->end
    // due to buddy system's property, for the latter 3 cases
    // reallocation of physical page(s) should be done if free_pages is true.
    vpn_t svpn = vpn;
    vpn_t evpn = vpn + npages;
    if (svpn == area->start && evpn == area->end) {
        pgtbl_unmap_range(vms->pgtbl, svpn, npages);
        if (free_pages) {
            pfree(area->sppn);
        }
        list_remove(&area->node);
        kmem_cache_free(&area_cache, area);
    } else if (svpn == area->start && evpn < area->end) {
        pgtbl_unmap_range(vms->pgtbl, svpn, npages);
        if (free_pages) {
            usize nremain_pages = area->end - evpn;
            ppn_t new_sppn = unwrap_err(palloc(nremain_pages));
            // copy old data.
            memcpy(
                (void*)PN2PA(new_sppn),
                (void*)PN2PA(area->sppn + npages),
                nremain_pages * PAGE_SIZE
            );
            pfree(area->sppn);
            area->sppn = new_sppn;
        }
        area->start = evpn;
    } else if (svpn > area->start && evpn == area->end) {
        pgtbl_unmap_range(vms->pgtbl, svpn, npages);
        if (free_pages) {
            usize nremain_pages = svpn - area->start;
            ppn_t new_sppn = unwrap_err(palloc(nremain_pages));
            // copy old data.
            memcpy(
                (void*)PN2PA(new_sppn),
                (void*)PN2PA(area->sppn),
                nremain_pages * PAGE_SIZE
            );
            pfree(area->sppn);
            area->sppn = new_sppn;
        }
        area->end = svpn;
    } else {
        // split area
        pgtbl_unmap_range(vms->pgtbl, svpn, npages);
        vm_area_t* left = unwrap_null(kmem_cache_alloc(&area_cache));
        vm_area_t* right = unwrap_null(kmem_cache_alloc(&area_cache));

        if (free_pages) {
            // allocate new sppns for both sides
            usize nleft_pages = svpn - area->start;
            usize nright_pages = area->end - evpn;

            ppn_t new_left_sppn = unwrap_err(palloc(nleft_pages));
            ppn_t new_right_sppn = unwrap_err(palloc(nright_pages));

            memcpy(
                (void*)PN2PA(new_left_sppn),
                (void*)PN2PA(area->sppn),
                nleft_pages * PAGE_SIZE
            );
            memcpy(
                (void*)PN2PA(new_right_sppn),
                (void*)PN2PA(area->sppn + (evpn - area->start)),
                nright_pages * PAGE_SIZE
            );
 
            pfree(area->sppn);
            left->sppn = new_left_sppn;
            right->sppn = new_right_sppn;
        }
        left->start = area->start;
        left->end = svpn;
        // for non-free_pages case, sppn can be arbitrary.
        // just ignore them here.
        left->type = area->type;
        left->flags = area->flags;
        right->start = evpn;
        right->end = area->end;
        right->type = area->type;
        right->flags = area->flags;
        list_push_back(&vms->areas, &left->node);
        list_push_back(&vms->areas, &right->node);
        list_remove(&area->node);
        kmem_cache_free(&area_cache, area);
    }
}

void
vm_unmap(
    vm_space_t* vms, 
    vpn_t vpn, 
    usize npages
) {
    vm_unmap_inner(vms, vpn, npages, true);
}

void
vm_activate(vm_space_t* vms) {
    // set the root page table
    pgtbl_activate(vms->pgtbl);
}

// currently page by page.
// we should do this area by area for better performance.
// refine later.
bool
vm_is_mapped(vm_space_t* vms, vpn_t vpn) {
    ppn_t placeholder;
    return pgtbl_lookup(vms->pgtbl, vpn, &placeholder);
}


// derive a kernel vm space from the global kernel_vms
// a deep copy is performed.
// MUST BE CALLED AFTER processor_init()
// note that scheduler kernel stack will also be derived here.
// may be a bit insecure if we allow user tasks to access kernel memory regions,
// but it's ok for now.
void
kvms_derive(vm_space_t* vms) {
    list_foreach(iter, &kernel_vms.areas) {
        vm_area_t* area = list_entry(iter, vm_area_t, node);
        usize npages = area->end - area->start;
        
        // in current design, only RESERVED areas exist in kernel_vms
        assert_eq(area->type, VM_RESERVED);
        assert((area->flags & VM_USER) == 0); // kernel area should not have VM_USER flag
        vm_map(
            vms,
            area->start,
            area->sppn,
            npages,
            area->type,
            area->flags
        );
    }
}

void
vm_dump(vm_space_t* vms) {
    trace("vm space dump:");
    list_foreach(iter, &vms->areas) {
        vm_area_t* area = list_entry(iter, vm_area_t, node);
        trace("  area [%lx, %lx) type=%s flags=%c%c%c",
            PN2PA(area->start), PN2PA(area->end),
            area->type == VM_RESERVED ? "RESERVED" :
            area->type == VM_ALLOCATED ? "ALLOCATED" : "UNKNOWN",
            (area->flags & VM_READ) ? 'r' : '-',
            (area->flags & VM_WRITE) ? 'w' : '-',
            (area->flags & VM_EXEC) ? 'x' : '-'
        );
    }
}