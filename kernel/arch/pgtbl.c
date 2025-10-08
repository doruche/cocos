/*
 * risc-v page table management (sv39)
 */

#include "kernel/arch/mm.h"
#include "kernel/misc/assert.h"
#include "kernel/misc/log.h"
#include "kernel/mm/pm.h"
#include "libs/types.h"

void
pgtbl_init(pgtbl_t* pgtbl) {
    assert(pgtbl != NULL);
    for (int i = 0; i < 512; i++) {
        pgtbl->entries[i] = 0;
    }
}

void
pgtbl_map(__root pgtbl_t *pgtbl, vpn_t vpn, ppn_t ppn, u64 flags) {
    
} 