/*
 * risc-v page table management (sv39)
 */

#include "kernel/arch/mm.h"
#include "libs/assert.h"
#include "libs/log.h"
#include "kernel/mm/pm.h"
#include "kernel/mm/vm.h"
#include "kernel/arch/csr.h"
#include "libs/types.h"

static pte_t*
pgtbl_find_pte(pgtbl_t *pgtbl, vpn_t vpn, bool alloc) {
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
            ppn_t new_table_ppn = unwrap_err(pm_alloc());
            pgtbl_init((pgtbl_t*)PN2PA(new_table_ppn));
            *pte = (new_table_ppn << 10) | PTE_V;
            table = (pgtbl_t*)PN2PA(new_table_ppn);
        } else {
            return NULL;
        }
    }
    unreachable()
}

static void
_pgtbl_walk(
    pgtbl_t* pgtbl, 
    pgtbl_leaf_walker leaf,
    pgtbl_branch_walker branch,
    void* ctx,
    vpn_t vpn_prefix,
    usize level
) {
    if (level >= 3) {
        unreachable();
    }

    for (usize i = 0; i < 512; i++) {
        pte_t* pte = &pgtbl->entries[i];
        vpn_t vpn = vpn_prefix | (i << ((2 - level) * 9));
        if (pte_is_branch(*pte)) {
            _pgtbl_walk(
                (pgtbl_t*)PTE2PA(*pte), 
                leaf, 
                branch, 
                ctx,
                vpn, 
                level + 1
            );
            if (branch != NULL) {
                branch(pgtbl, pte, ctx);
            }
        } else if (pte_is_leaf(*pte)) {
            if (leaf != NULL) {
                leaf(pgtbl, vpn, pte, ctx);
            }
        }
    }
}

// post-order traversal
// branches are always visited after leaves
// this allows us to do conditional unmapping easily
void
pgtbl_walk(
    pgtbl_t *pgtbl, 
    pgtbl_leaf_walker leaf,
    pgtbl_branch_walker branch,
    void* ctx
) {
    _pgtbl_walk(pgtbl, leaf, branch, ctx, 0, 0);
}

void
generic_branch_unmapper(
    pgtbl_t *pgtbl,
    pte_t* pte,
    void* ctx
) {
    bool child_exists = false;
    pgtbl_t* cur_table = (pgtbl_t*)PTE2PA(*pte);
    for (usize i = 0; i < 512; i++) {
        pte_t child = cur_table->entries[i];
        if (pte_is_mapped(child)) {
            child_exists = true;
            break;
        }
    }
    if (child_exists) {
        return;
    } else {
        // no mapped entries, we can free this pagetable
        assert(pm_decref(PA2PN((paddr_t)cur_table)));
        *pte = 0;
    }
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
    pte_t* pte = pgtbl_find_pte(pgtbl, vpn, true);
    assert(pte != NULL);

    if (pte_is_mapped(*pte)) {
        panic("pgtbl_map: already mapped");
    }

    *pte = (ppn << 10) | (flags & 0x3FF);
}

void
pgtbl_unmap(__root pgtbl_t *pgtbl, vpn_t vpn) {
    pte_t* pte = pgtbl_find_pte(pgtbl, vpn, false);

    if (pte == NULL || !pte_is_mapped(*pte)) {
        panic("pgtbl_unmap: not mapped vpn %p", vpn);
    }

    *pte = 0;
}

/// note that we assume if the valid bit is set, the entry is valid.
/// so for unmapped entries, we must keep them zeroed.
/// this is assured by pgtbl_init.
/// do not unmap/destroy base mappings.
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
    // pagetable should be freed
    assert(pm_decref(PA2PN((paddr_t)pgtbl)));
}

void
pgtbl_activate(pgtbl_t *pgtbl) {
    flush_tlb();
    w_satp(SATP(pgtbl));
}

vm_flags_t
pte_archflag2vmflag(u64 flags) {
    vm_flags_t vmflags = 0;
    if (flags & PTE_R) vmflags |= VM_READ;
    if (flags & PTE_W) vmflags |= VM_WRITE;
    if (flags & PTE_X) vmflags |= VM_EXEC;
    if (flags & PTE_U) vmflags |= VM_USER;
    if ((flags & PTE_V) == 0) vmflags |= VM_FAKE; // not valid means fake mapping
    return vmflags;
}

u64
pte_vmflag2archflag(vm_flags_t flags) {
    u64 archflags = 0;
    archflags |= PTE_V;
    if (flags & VM_READ) archflags |= PTE_R;
    if (flags & VM_WRITE) archflags |= PTE_W;
    if (flags & VM_EXEC) archflags |= PTE_X;
    if (flags & VM_USER) archflags |= PTE_U;
    if (flags & VM_FAKE) archflags &= ~PTE_V; // fake mapping means not valid

    return archflags;
}

bool
pgtbl_lookup(pgtbl_t* pgtbl, vpn_t vpn, ppn_t* out_ppn) {
    pte_t* pte = pgtbl_find_pte(pgtbl, vpn, false);
    if (pte == NULL || !pte_is_mapped(*pte)) {
        return false;
    }
    *out_ppn = PTE2PPN(*pte);
    return true;
}

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
            trace("%s[%d] -> branch to %p\n", prefix[level], i, (void*)PTE2PA(pte));
            _pgtbl_dump((pgtbl_t*)PTE2PA(pte), level + 1);
        } else if (pte_is_leaf(pte)) {
            trace("%s[%d] -> leaf to %p (flags: 0x%lx)\n", prefix[level], i, (void*)PTE2PA(pte), pte & 0x3FF);
        }
    }
}

// too tedious. refine later
void
pgtbl_dump(pgtbl_t *pgtbl) {
    _pgtbl_dump(pgtbl, 0);
}