/*
 * physical page frame allocator. simple buddy system.
 */

#pragma once

#include "libs/types.h"

#define BUDDY_MAX_ORDER 14 // max block size is 4KB * 2^14 = 64MB

#define NPMZONE_MAX 4

typedef struct _buddy_bitmap_t {
    usize order;
    // we may only use part of the units in the last byte. 
    // this field helps us to know how many units are valid.
    usize nunits; 
    u8 bitmap[0];
#define BUDDY_BLK_AVAIL 0
#define BUDDY_BLK_USED  1

} buddy_bitmap_t;

typedef struct _page_t {
    usize order; // order of the block this page belongs to

    // we may extend this struct later
} page_t;

typedef struct _pm_zone_t {
    // header
    ppn_t start; // start ppn of this zone. the same as bitmaps.
    usize npages; // allocatable pages in this zone.
    usize nfree;  // free pages in this zone
    
    // pages metadata
    page_t* pages; // array of npages page_t structs. do not count the pages used by bitmaps.

    // buddy system
    ppn_t salloc; // start of allocatable pages
    buddy_bitmap_t* bitmaps;
} pm_zone_t;

typedef struct _bootinfo_t bootinfo_t;
void    pm_init(bootinfo_t* bootinfo);
isize   palloc(usize npages);
isize   palloc_one(void);
void    pfree(ppn_t ppn);

usize   pm_count_free(void);

void    pm_dump(void);