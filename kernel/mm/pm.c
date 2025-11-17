/*
 * physical page allocator
 */

#include <libs/prelude.h>
#include <kernel/arch/arch.h>
#include <kernel/mm/pm.h>

// simple linked list based physical page allocator
// used to try buddy system but gave up due to complexity

static pm_zone_t pmzones[NPMZONE_MAX];
static usize npmzones = 0;

static bool
ppn_in_zone(pm_zone_t* zone, ppn_t ppn) {
    return ppn >= zone->salloc && ppn < zone->salloc + zone->npages;
}

static ppn_t
run2ppn(pm_zone_t* zone, page_run_t* run) {
    ppn_t ppn = zone->salloc + ((paddr_t)run - PN2PA(zone->spagerun)) / sizeof(page_run_t);
    assert(ppn_in_zone(zone, ppn));
    return ppn;
}

static page_run_t*
ppn2run(pm_zone_t* zone, ppn_t ppn) {
    assert(ppn_in_zone(zone, ppn));
    usize offset = ppn - zone->salloc;
    return (page_run_t*)PN2PA(zone->spagerun) + offset;
}

static pm_zone_t
pm_zone_init(ppn_t start, ppn_t end) {
    pm_zone_t zone;
    
    usize nalloc_pages_est = (end - start) * PAGE_SIZE / (sizeof(page_run_t) + PAGE_SIZE);
    zone.spagerun = start;
    zone.salloc = end - nalloc_pages_est;
    zone.freelist = NULL;

    // init freelist
    usize cur_ptr = 0;
    for (usize i = 0; i < nalloc_pages_est; i++) {
        // page_run_t* run = ppn2run(&zone, zone.salloc + i);
        page_run_t* run = (page_run_t*)PN2PA(zone.spagerun) + i;
        run->ref = 0;
        run->next = zone.freelist;
        zone.freelist = run;
        cur_ptr += sizeof(page_run_t);
    }
    cur_ptr = align_up(cur_ptr, PAGE_SIZE);
    usize nalloc_pages = (end - start) - (cur_ptr / PAGE_SIZE);
    zone.npages = nalloc_pages;
    zone.nfree = nalloc_pages;    

    return zone;
}

void
pm_init(bootinfo_t* bootinfo) {
    // find free memory from bootinfo
    bool freemem_exist = false;
    for(usize i = 0; i < NMEMZONE_MAX; i++) {
        if(bootinfo->zones[i].type == MEMZONE_FREE) {
            freemem_exist = true;

            memzone_t *freezone = &bootinfo->zones[i];
            paddr_t smem = PGDOWN(freezone->start);
            paddr_t emem = PGUP(freezone->end);

            pm_zone_t zone = pm_zone_init(PA2PN(smem), PA2PN(emem));

            pr_info("pmzone found:[%p - %p) - (%d pages)", smem, emem, (emem - smem) / PAGE_SIZE);
            pr_trace("spagerun=%p, salloc=%p, npages=%d, nfree=%d",
                PN2PA(zone.spagerun), PN2PA(zone.salloc), zone.npages, zone.nfree);

            pmzones[npmzones++] = zone;
        } else if (bootinfo->zones[i].type == MEMZONE_NONE) {
                break;
        }
    }

    assert(freemem_exist);
}

ppn_t
pm_alloc(void) {
    for (usize i = 0; i < npmzones; i++) {
        pm_zone_t* zone = pmzones + i;
        if (zone->nfree > 0) {
            page_run_t* run = zone->freelist;
            zone->freelist = run->next;
            run->next = NULL;
            assert_eq(run->ref, 0);
            run->ref = 1; // set ref to 1
            zone->nfree--;
            return run2ppn(zone, run);
        }
    }
    panic("pm_alloc: out of memory");
}

bool
pm_decref(ppn_t ppn) {
    for (usize i = 0; i < npmzones; i++) {
        pm_zone_t* zone = pmzones + i;
        if (ppn_in_zone(zone, ppn)) {
            page_run_t* run = ppn2run(zone, ppn);
            assert(run->ref > 0);
            run->ref--;
            pr_trace("pm_decref: ppn=%p, ref %d -> %d", PN2PA(ppn), run->ref + 1, run->ref);
            if (run->ref == 0) {
                run->next = zone->freelist;
                zone->freelist = run;
                zone->nfree++;
                return true;
            }
            return false;
        }
    }
    panic("pfree: invalid ppn %p", PN2PA(ppn));
}

void
pm_incref(ppn_t ppn) {
    for (usize i = 0; i < npmzones; i++) {
        pm_zone_t* zone = pmzones + i;
        if (ppn_in_zone(zone, ppn)) {
            page_run_t* run = ppn2run(zone, ppn);
            assert(run->ref > 0); // can not increase ref of free page
            run->ref++;
            pr_trace("pm_increase_ref: ppn=%p, ref %d -> %d", PN2PA(ppn), run->ref - 1, run->ref);
            return;
        }
    }
    panic("pm_increase_ref: invalid ppn %p", PN2PA(ppn));
}

usize
pm_getref(ppn_t ppn) {
    for (usize i = 0; i < npmzones; i++) {
        pm_zone_t* zone = pmzones + i;
        if (ppn_in_zone(zone, ppn)) {
            page_run_t* run = ppn2run(zone, ppn);
            return run->ref;
        }
    }
    panic("pm_getref: invalid ppn %p", PN2PA(ppn));
}

usize
pm_count_free(void) {
    usize nfree = 0;
    for (usize i = 0; i < npmzones; i++) {
        pm_zone_t* zone = pmzones + i;
        nfree += zone->nfree;
    }
    return nfree;
}

void
pm_dump(void) {
    pr_info("------ pm dump ------");
    for (usize i = 0; i < npmzones; i++) {
        pm_zone_t* zone = pmzones + i;
        pr_info("pmzone %d: spagerun=%p, salloc=%p, npages=%d, nfree=%d",
            i,
            PN2PA(zone->spagerun),
            PN2PA(zone->salloc),
            zone->npages,
            zone->nfree
        );
    }
    pr_info("------ pm dump end ------");
}