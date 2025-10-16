/*
 * DEPRECATED: singly linked list based simple page-level. use buddy system based allocator instead.
 * physical memory allocator. allocates by pagesize. 
 */

#pragma once

#include "libs/types.h"
#include "kernel/boot.h"

typedef struct _page_run_t {
    usize ref;
    struct _page_run_t* next;
} page_run_t;

typedef struct _pm_zone_t {
    ppn_t spagerun;
    ppn_t salloc;
    usize npages; // number of allocatable pages
    usize nfree;
    page_run_t* freelist; // use a list to speed up allocation
} pm_zone_t;


#define NPMZONE_MAX 4

void    pm_init(bootinfo_t* bootinfo);
ppn_t   palloc(void);
void    pfree(ppn_t ppn);
void    pm_increase_ref(ppn_t ppn);
usize   pm_get_ref(ppn_t ppn);

usize   pm_count_free(void);