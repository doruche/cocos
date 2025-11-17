#include "kernel/mm/deprecated/pm.h"
#include "kernel/boot.h"
#include "kernel/arch/mm.h"
#include "libs/prelude.h"

static pm_zone_t pmzones[NPMZONE_MAX];

static usize npmzones = 0;

/// get bitmap with next lower order
static inline buddy_bitmap_t*
next_bitmap(buddy_bitmap_t* cur) {
    return (buddy_bitmap_t*)align_up(
        (u8*)cur + sizeof(buddy_bitmap_t) + (cur->nunits + 7) / 8, 
        8
    );
}

static inline buddy_bitmap_t*
get_bitmap(pm_zone_t* zone, usize order) {
    assert(order <= BUDDY_MAX_ORDER);
    buddy_bitmap_t* cur = zone->bitmaps;
    loop {
        if (cur->order == order) {
            return cur;
        }
        cur = next_bitmap(cur);
    }
}

static inline void
bm_set(buddy_bitmap_t* bm, usize unit_idx) {
    assert(unit_idx < bm->nunits);
    usize byte_idx = unit_idx / 8;
    usize bit_idx = unit_idx % 8;
    bm->bitmap[byte_idx] |= (1 << bit_idx);
}

static inline void
bm_clear(buddy_bitmap_t* bm, usize unit_idx) {
    assert(unit_idx < bm->nunits);
    usize byte_idx = unit_idx / 8;
    usize bit_idx = unit_idx % 8;
    bm->bitmap[byte_idx] &= ~(1 << bit_idx);
}

static inline bool
bm_test(buddy_bitmap_t* bm, usize unit_idx) {
    assert(unit_idx < bm->nunits);
    usize byte_idx = unit_idx / 8;
    usize bit_idx = unit_idx % 8;
    return (bm->bitmap[byte_idx] & (1 << bit_idx)) != 0;
}

static void
pm_zone_init(pm_zone_t* zone, memzone_t* freemem) {
    zone->start = PA2PN(freemem->start);
    zone->pages = (page_t*)freemem->start;

    // init buddy system
    // layout: |'page_t's|bitmap[2^<BUDDY_MAX_ORDER - 1>KB]|...|bitmap[8KB]|bitmap[4KB]|pad|allocatable pages...|

    // a chicken and egg problem. how can we know how many pages are allocatable,
    // without knowing how many pages are used by the bitmaps?

    // we use a 2-pass approach: 
    // overestimate the number of allocatable pages at first, then
    // find out how many pages are actually used by the bitmaps.
    // this is a pessimistic approach. it may be inefficient, but absolutely correct.

    usize npages_est = (freemem->end - freemem->start) / PAGE_SIZE;
    zone->bitmaps = (buddy_bitmap_t*)((u8*)zone->pages + sizeof(page_t) * npages_est);

    buddy_bitmap_t* cur = zone->bitmaps;
    for (isize order = BUDDY_MAX_ORDER; order >= 0; order--) {
        usize block_size = (1 << order); // in pages
        usize nunits_est = npages_est / block_size;
        if (nunits_est == 0) {
            // this order is not usable
            continue;   
        }
        cur->nunits = nunits_est;
        cur = next_bitmap(cur);
    }

    // now cur points to the end of the last bitmap.
    // align it to next page boundary, and that is the start of allocatable pages.
    ppn_t salloc = PA2PN(PGUP((u64)cur));
    assert(salloc < PA2PN(freemem->end));

    zone->salloc = salloc;
    zone->npages = freemem->end / PAGE_SIZE - salloc;
    zone->nfree = zone->npages;

    // currently each page_t is just a thin wrapper of usize,
    // so we just use a simple memset here.

    // set an invalid order.
    memset(zone->pages, BUDDY_MAX_ORDER + 1, sizeof(page_t) * zone->npages);

    // initialize bitmaps, accurately.
    cur = zone->bitmaps;
    for (isize order = BUDDY_MAX_ORDER; order >= 0; order--) {
        usize unit_size = 1 << order;
        usize nunits = zone->npages / unit_size;
        if (nunits == 0) {
            // if no unit is usable, skip this order,
            // thus saving some space.
            continue;
        }
        cur->order = order;
        cur->nunits = nunits;
        memset(cur->bitmap, 0xFF, (nunits + 7) / 8);
        cur = next_bitmap(cur);
    }
    // mark units as free.
    // e.g. we hold 97 MB and max unit is 64 MB. we have to
    // mark one 64 MB unit, one 32 MB unit, and one 1 MB unit as free.
    // a top-down greedy approach works.
    // ---
    //    --
    //      --
    //        ---
    // like this.
    usize npages = zone->npages;
    usize cur_npages = 0;

    for (isize order = BUDDY_MAX_ORDER; order >= 0; order--) {
        usize unit_size = 1 << order;
        usize sunit_idx = cur_npages / unit_size;
        usize unit_idx = sunit_idx;

        if (cur_npages + unit_size > npages) {
            continue;
        }
        while (cur_npages + unit_size <= npages) {
            buddy_bitmap_t* bm = get_bitmap(zone, order);
            unit_idx = cur_npages / unit_size;
            assert(unit_idx < bm->nunits);
            bm_clear(bm, unit_idx);
            cur_npages += unit_size;
        }

        pr_trace("pm_zone_init: order %d, free unit_idx [%ld , %ld)",
            order,
            sunit_idx,
            unit_idx + 1
        );
        if (cur_npages == npages) {
            break;
        }
    }
    assert_eq(cur_npages, npages);
}

void
pm_init(bootinfo_t* bootinfo) {
    bool freemem_exist = false;
    for (usize i = 0; i < NMEMZONE_MAX; i++) {
        if (bootinfo->zones[i].type == MEMZONE_NONE) {
            break;
        }
        if (bootinfo->zones[i].type == MEMZONE_FREE) {
            freemem_exist = true;

            pm_zone_t* zone = &pmzones[npmzones];
            pm_zone_init(zone, &bootinfo->zones[i]);
            npmzones++;
        }
    }
    assert(freemem_exist);
}

static inline usize
get_order(usize npages) {
    usize order = 0;
    usize p = 1;
    while (p < npages) {
        order++;
        p <<= 1;
    }
    return order;
}

static isize
palloc_in_zone(pm_zone_t* zone, usize npages) {
    if (npages == 0 || npages > zone->nfree) {
        return -ENOMEM;
    }
    usize order = get_order(npages);
    if (order > BUDDY_MAX_ORDER) {
        return -ENOMEM;
    }


    isize found_order = -1;
    isize unit_idx = -1;

    buddy_bitmap_t* bm;
    for (usize i = order; i <= BUDDY_MAX_ORDER; i++) {
        bm = get_bitmap(zone, i);
#ifdef DEBUG
        // do some sanity check
        assert_eq(bm->order, i);
        assert(bm->nunits > 0);
#endif
        for (usize u = 0; u < bm->nunits; u++) {
            if (!bm_test(bm, u)) {
                found_order = i;
                unit_idx = u;
                goto found;
            }
        }
    
    }

    return 0;

found:

    bm_set(bm, unit_idx);

    // top down split
    while (found_order > order) {
        found_order--;
        buddy_bitmap_t* lower_bm = get_bitmap(zone, found_order);
        // use the first half.
        unit_idx <<= 1;
        usize buddy_idx = unit_idx + 1;
    
        bm_set(lower_bm, unit_idx);
        bm_clear(lower_bm, buddy_idx);
    }

    zone->nfree -= (1 << order);

    ppn_t ppn = zone->salloc + unit_idx * (1 << order);
    usize page_idx = ppn - zone->salloc;
    zone->pages[page_idx].order = order;

    return ppn;
}

isize
palloc(usize npages) {
    if (npages == 0) {
        return -EINVAL;
    }

    for (usize i = 0; i < npmzones; i++) {
        pm_zone_t* zone = &pmzones[i];
        isize ppn = palloc_in_zone(zone, npages);
        if (ppn >= 0) {
            return ppn;
        } else if (ppn != -ENOMEM) {
            // some unexpected error
            return ppn;
        }
    }

    return -ENOMEM;
}

// used when there is no enough contiguous pages
// altually almost all incontiguous problems can be solved by being mapped contiguously.
// so this function serves as a last resort.
isize
palloc_one(void) {
    for (usize i = 0; i < npmzones; i++) {
        pm_zone_t* zone = &pmzones[i];
        isize ppn = palloc_in_zone(zone, 1);
        if (ppn >= 0) {
            return ppn;
        } else if (ppn != -ENOMEM) {
            // some unexpected error
            return ppn;
        }
    }

    panic("palloc_one: out of memory");
    // return -ENOMEM;
}

static inline bool
ppn_in_zone(pm_zone_t* zone, ppn_t ppn) {
    return ppn >= zone->salloc && ppn < zone->salloc + zone->npages;
}

static void
pfree_in_zone(pm_zone_t* zone, ppn_t ppn) {
    usize page_idx = ppn - zone->salloc;
    usize order = zone->pages[page_idx].order;
    assert_ne(order, BUDDY_MAX_ORDER + 1);
    zone->pages[page_idx].order = BUDDY_MAX_ORDER + 1; // mark as free

    usize unit_idx = page_idx >> order;

    for (usize o = order; o <= BUDDY_MAX_ORDER; o++) {
        buddy_bitmap_t* bm = get_bitmap(zone, o);
        assert(bm_test(bm, unit_idx));
        bm_clear(bm, unit_idx);

        usize buddy_idx = unit_idx ^ 1; // for even, plus 1; for odd, minus 1

        if (buddy_idx >= bm->nunits || bm_test(bm, buddy_idx)) {
            break;
        }

        // merge
        // to merge up, we should set these two buddies as used in the lower order bitmap.
        bm_set(bm, buddy_idx);
        bm_set(bm, unit_idx);
        unit_idx >>= 1;
    }

    zone->nfree += (1 << order);
}

void
pfree(ppn_t ppn) {
    for (usize i = 0; i < npmzones; i++) {
        pm_zone_t* zone = &pmzones[i];
        if (ppn_in_zone(zone, ppn)) {
            pfree_in_zone(zone, ppn);
            return;
        }
    }

    panic("pfree: ppn 0x%lx not in any zone", ppn);
}

/// dump free units in each order
void
pm_dump(void) {
    // a top-down dump

    pr_info("pm zones:");

    for (usize i = 0; i < npmzones; i++) {
        pm_zone_t* zone = &pmzones[i];
        pr_info("zone %d: start ppn = 0x%lx, npages = %ld, nfree = %ld", 
            i, zone->start, zone->npages, zone->nfree);
        buddy_bitmap_t* cur = get_bitmap(zone, BUDDY_MAX_ORDER);
        loop {
            bit_traverse(cur->bitmap, cur->nunits, byte_idx, bit_idx) {
                usize unit_idx = byte_idx * 8 + bit_idx;
                if (!bm_test(cur, unit_idx)) {
                    pr_info("  order %d: free unit %ld, ppn 0x%lx", 
                        cur->order, unit_idx, zone->salloc + unit_idx * (1 << cur->order));
                }
            }
            if (cur->order == 0) {
                break;
            }
            cur = next_bitmap(cur);
        }    
    }
    pr_info("end of pm dump.");
}

usize
pm_count_free(void) {
    usize total = 0;
    for (usize i = 0; i < npmzones; i++) {
        total += pmzones[i].nfree;
    }
    return total;
}