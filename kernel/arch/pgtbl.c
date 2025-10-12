/*
 * risc-v page table management (sv39)
 */

#include "kernel/arch/mm.h"
#include "kernel/misc/assert.h"
#include "kernel/misc/log.h"
#include "kernel/mm/pm.h"
#include "kernel/mm/vm.h"
#include "kernel/arch/csr.h"
#include "libs/types.h"

static bool
pte_is_leaf(pte_t pte) {
    return (pte & (PTE_R | PTE_W | PTE_X)) != 0 && (pte & PTE_V) != 0;
}

static bool
pte_is_branch(pte_t pte) {
    return (pte & (PTE_R | PTE_W | PTE_X)) == 0 && (pte & PTE_V) != 0;
}

static bool
pte_is_mapped(pte_t pte) {
    return (pte & PTE_V) != 0;
}

pte_t*
pgtbl_walk(pgtbl_t *pgtbl, vpn_t vpn, bool alloc) {
    usize indices[3] = {
        (vpn >> 18) & 0x1FF,
        (vpn >> 9) & 0x1FF,
        vpn & 0x1FF
    };

    pgtbl_t* table = pgtbl;
    for (usize level = 0; level < 3; level++) {
        pte_t* pte = &table->entries[indices[level]];
        if (level == 2) {
            return pte;
        }
        if (pte_is_branch(*pte)) {
            table = (pgtbl_t*)PTE2PA(*pte);
        } else if (alloc) {
            ppn_t new_table_ppn = palloc();
            if (new_table_ppn == 0) {
                warn("pgtbl_walk: out of memory");
                return NULL;
            }
            pgtbl_init((pgtbl_t*)PN2PA(new_table_ppn));
            *pte = (new_table_ppn << 10) | PTE_V;
            table = (pgtbl_t*)PN2PA(new_table_ppn);
        } else {
            return NULL;
        }
    }

    unreachable()
}

void
pgtbl_init(pgtbl_t* pgtbl) {
    assert(pgtbl != NULL);
    for (int i = 0; i < 512; i++) {
        pgtbl->entries[i] = 0;
    }
}

void
pgtbl_map(__root pgtbl_t *pgtbl, vpn_t vpn, ppn_t ppn, u64 flags) {
    pte_t* pte = pgtbl_walk(pgtbl, vpn, true);
    assert(pte != NULL);

    if (pte_is_mapped(*pte)) {
        panic("pgtbl_map: already mapped");
    }

    *pte = (ppn << 10) | (flags & 0x3FF);
}

void
pgtbl_unmap(__root pgtbl_t *pgtbl, vpn_t vpn) {
    pte_t* pte = pgtbl_walk(pgtbl, vpn, false);
    assert(pte != NULL);

    if (!pte_is_mapped(*pte)) {
        panic("pgtbl_unmap: not mapped");
    }

    *pte = 0;
}

/// note that we assume if the valid bit is set, the entry is valid.
/// so for unmapped entries, we must keep them zeroed.
/// this is assured by pgtbl_init.
void
pgtbl_destroy(pgtbl_t *pgtbl) {
    for (int i = 0; i < 512; i++) {
        pte_t *pte = &pgtbl->entries[i];
        if (pte_is_branch(*pte)) {
            pgtbl_destroy((pgtbl_t*)PTE2PA(*pte));
        } else if (pte_is_leaf(*pte)) {
            // should not have any mapped entries when destroying
            // these should be removed when reclaiming memory
            panic("pgtbl_destroy: leaf entry found");
        }
    }
    pfree(PA2PN((paddr_t)pgtbl));
}

void
pgtbl_activate(pgtbl_t *pgtbl) {
    flush_tlb();
    w_satp(SATP(pgtbl));
}

vm_area_flags_t
pte_archflag2vmflag(u64 flags) {
    vm_area_flags_t vmflags = 0;
    if (flags & PTE_R) vmflags |= VM_READ;
    if (flags & PTE_W) vmflags |= VM_WRITE;
    if (flags & PTE_X) vmflags |= VM_EXEC;
    if (flags & PTE_U) vmflags |= VM_USER;
    if ((flags & PTE_V) == 0) vmflags |= VM_FAKE; // not valid means fake mapping
    return vmflags;
}

// sv39
u64
pte_vmflag2archflag(vm_area_flags_t flags) {
    u64 archflags = 0;
    archflags |= PTE_V;
    if (flags & VM_READ) archflags |= PTE_R;
    if (flags & VM_WRITE) archflags |= PTE_W;
    if (flags & VM_EXEC) archflags |= PTE_X;
    if (flags & VM_USER) archflags |= PTE_U;
    if (flags & VM_FAKE) archflags &= ~PTE_V; // fake mapping, not valid

    return archflags;
}

ppn_t
pgtbl_lookup(pgtbl_t *pgtbl, vpn_t vpn) {
    pte_t* pte = pgtbl_walk(pgtbl, vpn, false);
    if (pte == NULL || !pte_is_mapped(*pte) || !pte_is_leaf(*pte)) {
        return 0;
    }
    return PTE2PPN(*pte);
}

#ifdef PGTBL_DEBUG

static void
_pgtbl_dump(pgtbl_t *pgtbl, int level) {
    static const char* const prefix[] = {
        "",
        "\t",
        "\t\t",
    };

    for (int i = 0; i < 512; i++) {
        pte_t pte = pgtbl->entries[i];
        if (pte_is_branch(pte)) {
            printk("%s[%d] -> branch to %p\n", prefix[level], i, (void*)PTE2PA(pte));
            _pgtbl_dump((pgtbl_t*)PTE2PA(pte), level + 1);
        } else if (pte_is_leaf(pte)) {
            printk("%s[%d] -> leaf to %p (flags: 0x%03lx)\n", prefix[level], i, (void*)PTE2PA(pte), pte & 0x3FF);
        }
    }
}

void
pgtbl_dump(pgtbl_t *pgtbl) {
    _pgtbl_dump(pgtbl, 0);
}

#endif