/*
 * physical page allocator
 */

#include "kernel/boot.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "kernel/mm/pm.h"
#include "libs/types.h"
#include "kernel/boot.h"
#include "kernel/arch/mm.h"

static page_run_t* free_list = NULL;

void
palloc_init(bootinfo_t* bootinfo) {
    // find free memory from bootinfo
    usize freezone_idx = NMEMZONE_MAX;
    for(usize i = 0; i < NMEMZONE_MAX; i++) {
        if(bootinfo->zones[i].type == MEMZONE_FREE) {
            freezone_idx = i;
            break;
        } else if (bootinfo->zones[i].type == MEMZONE_NONE) {
            break;
        }
    }

    assert(freezone_idx < NMEMZONE_MAX);

    memzone_t *freezone = &bootinfo->zones[freezone_idx];
    paddr_t smem = PGDOWN(freezone->start);
    paddr_t emem = PGUP(freezone->end);

    for (paddr_t addr = smem; addr < emem; addr += PAGE_SIZE) {
        page_run_t* page = (page_run_t*)addr;
        page->ref = 0;
        page->next = free_list;
        free_list = page;
    }

    usize npages = (emem - smem) / PAGE_SIZE;
    info("free memory: [%p - %p) - (%d pages)", smem, emem, npages);
}

static inline ppn_t
page_to_ppn(page_run_t* page) {
    return (u64)page >> PAGE_SHIFT;
}

static inline page_run_t*ppn_to_page(ppn_t ppn) {
    return (page_run_t*)(ppn << PAGE_SHIFT);
}

ppn_t
palloc(void) {
    if (free_list == NULL) {
        return 0;
    }

    page_run_t* page = free_list;
    free_list = page->next;
    page->next = NULL;
    page->ref = 1;

    return page_to_ppn(page);
}

void
pfree(ppn_t ppn) {
    page_run_t* page = ppn_to_page(ppn);
    assert(page->ref > 0);
    page->ref--;
    if (page->ref == 0) {
        page->next = free_list;
        free_list = page;
    }
}