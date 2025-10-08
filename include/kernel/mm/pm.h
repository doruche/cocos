/*
 * physical memory allocator. allocates by pagesize. 
 */

#ifndef _K_MM_PALLOC_H
#define _K_MM_PALLOC_H 1

#ifndef __DEFONLY__

#include "libs/types.h"
#include "kernel/boot.h"

typedef struct _page_run_t {
    struct _page_run_t* next;
    u64 ref;
} page_run_t;

void    palloc_init(bootinfo_t* bootinfo);
ppn_t   palloc(void);
void   pfree(ppn_t ppn);


#endif

#endif