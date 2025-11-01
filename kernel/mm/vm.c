#include "kernel/mm/vm.h"
#include "kernel/arch/mm.h"
#include "kernel/mm/pm.h"
#include "kernel/mm/slab.h"
#include "libs/list.h"
#include "libs/prelude.h"
#include "kernel/mm/kmalloc.h"
#include "libs/iter.h"
#include "kernel/arch/board.h"

/* 
 * to manage kernel and user vm spaces, we adopt a simple strategy:
 * 1. kernel space is static, we map all the memory regions at once during boot
 * 2. user space is cloned from kernel space at initialization,
 *  then mapped on demand during runtime.
 * must notice that kernel only handles kernel space mappings,
 * user space mappings must be handled by pm and pager server.
 * and if we found any user space mappings here, we panic.
 */

vm_space_t kernel_vms;

void
kvms_init(bootinfo_t* bootinfo) {
    vm_init(&kernel_vms);

    for (usize i = 0; i < NMEMZONE_MAX; i++) {
        memzone_t* zone = &bootinfo->zones[i];

        vm_flags_t flags = 0;        
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
            (vpn_t)PA2PN(zone->start),
            (ppn_t)PA2PN(zone->start),
            (zone->end - zone->start) / PAGE_SIZE,
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

    vm_activate(&kernel_vms);
}

void
vm_init(vm_space_t* vms) {
    ppn_t pgtbl_ppn = unwrap_err(pm_alloc());
    vms->pgtbl = (pgtbl_t*)PN2PA(pgtbl_ppn);
    pgtbl_init(vms->pgtbl);
}

static void
kern_leaf_unmapper(
    pgtbl_t *kernel_pgtbl, 
    vpn_t vpn, 
    pte_t* pte,
    void* ctx
) {
    if (PN2PA(vpn) >= KERN_BASE) {
        // user/kernel stacks should be unmapped and reclaimed by actx_destroy()
        *pte = 0;
    } else {
        panic("vm_destroy: user mapping found at vpn %lx", PN2PA(vpn));
    }
}

// as described before, we only need to clear mappings here.
// memory regions except for the kernel space should be reclaimed by pm/pager server
// when tasks exit.
void
vm_destroy(vm_space_t* vms) {
    // if uspace servers are implemented correctly,
    // we could just call pgtbl_clear to remove kernel mappings
    // but for sanity check, we only clear kernel mappings here,
    // and see if there're any user mappings left.
    // if so, panic, thus detect bugs in uspace servers.
    pgtbl_walk(
        vms->pgtbl, 
        kern_leaf_unmapper,
        generic_branch_unmapper,
        NULL
    );

    notify("free pages before destroying pgtbl: %ld", pm_count_free());
    pgtbl_destroy(vms->pgtbl); // all mappings should be removed
    notify("free pages after destroying pgtbl: %ld", pm_count_free());
}

void
vm_map(
    vm_space_t* vms, 
    vpn_t vpn, 
    ppn_t ppn,
    usize npages,
    vm_flags_t flags
) {
    if (npages == 0) {
        panic("vm_map: mapping zero pages at vpn %lx", PN2PA(vpn));
    }

    for (usize i = 0; i < npages; i++) {
        pgtbl_map(
            vms->pgtbl,
            vpn + i,
            ppn + i,
            pte_vmflag2archflag(flags)
        );
    }

    trace("vm_map: mapped ppn [0x%lx, 0x%lx) to vpn [0x%lx, 0x%lx), flags 0x%x",
        ppn,
        ppn + npages,
        vpn,
        vpn + npages,
        flags
    );
}

void
vm_unmap(
    vm_space_t* vms, 
    vpn_t vpn, 
    usize npages
) {
    for (usize i = 0; i < npages; i++) {
        pgtbl_unmap(vms->pgtbl, vpn + i);
    }
}

// allocate physical pages and map them to the given virtual pages
isize
vm_alloc(
    vm_space_t* vms,
    vpn_t vpn,
    usize npages,
    vm_flags_t flags
) {
    for (usize i = 0; i < npages; i++) {
        if (vm_is_mapped(vms, vpn + i)) {
            return -ERR_EXIST;
        }
    }
    for (usize i = 0; i < npages; i++) {
        ppn_t ppn = unwrap_err(pm_alloc());
        pgtbl_map(
            vms->pgtbl,
            vpn + i,
            ppn,
            pte_vmflag2archflag(flags)
        );
    }
    return 0;
}

static isize
vm_memcpy_callback(
    const range_t* chunk,
    void* ctx
) {
    struct {
        kaddr_t src;
        vm_space_t* vms;
    } *state = ctx;
    ppn_t ppn;
    if (!pgtbl_lookup(state->vms->pgtbl, PA2PN(chunk->start), &ppn)) {
        warn("vm_memcpy: unmapped vpn %lx", PA2PN(chunk->start));
        return -ERR_FAULT;
    }
    usize inpage_offset = chunk->start % PAGE_SIZE;
    usize inpage_len = chunk->end - chunk->start;
    memcpy(
        (void*)(PN2PA(ppn) + inpage_offset),
        (const void*)state->src,
        inpage_len
    );
    state->src += inpage_len;
    return 0;
}

isize vm_memcpy(
    vm_space_t* vms,
    vaddr_t dst,
    kaddr_t src,
    usize len
) {
    return unwrap_err(range_iter(
        &(range_t) {
            .start = dst,
            .end = dst + len,
        },
        PAGE_SIZE,
        vm_memcpy_callback,
        &(struct {
            kaddr_t src;
            vm_space_t* vms;
        }) {
            .src = src,
            .vms = vms,
        }
    ));
}

static isize
vm_memset_callback(
    const range_t* chunk,
    void* ctx
) {
    struct {
        u8 val;
        vm_space_t* vms;
    } *state = ctx;
    ppn_t ppn;
    if (!pgtbl_lookup(state->vms->pgtbl, PA2PN(chunk->start), &ppn)) {
        warn("vm_memset: unmapped vpn %lx", PA2PN(chunk->start));
        return -ERR_FAULT;
    }
    usize inpage_offset = chunk->start % PAGE_SIZE;
    usize inpage_len = chunk->end - chunk->start;
    memset(
        (void*)(PN2PA(ppn) + inpage_offset),
        state->val,
        inpage_len
    );
    return 0;
}

isize
vm_memset(
    vm_space_t* vms,
    vaddr_t dst,
    u8 value,
    usize len
) {
    return unwrap_err(range_iter(
        &(range_t) {
            .start = dst,
            .end = dst + len,
        },
        PAGE_SIZE,
        vm_memset_callback,
        &(struct {
            u8 val;
            vm_space_t* vms;
        }) {
            .val = value,
            .vms = vms,
        }
    ));
}

bool
vm_is_mapped(vm_space_t* vms, vpn_t vpn) {
    pte_t placeholder;
    return pgtbl_lookup(vms->pgtbl, vpn, &placeholder);
}

void
vm_activate(vm_space_t* vms) {
    pgtbl_activate(vms->pgtbl);
}

void
vm_dump(vm_space_t* vms) {
    pgtbl_dump(vms->pgtbl);
}

static void
kvms_derive_walker(
    pgtbl_t *kernel_pgtbl, 
    vpn_t vpn,
    pte_t* pte,
    void* ctx
) {
    if (pte_is_mapped(*pte)) {
        assert(PN2PA(vpn) >= KERN_BASE);
        pgtbl_map(
            (pgtbl_t*)ctx,
            vpn,
            PTE2PPN(*pte),
            PTE_FLAGS(*pte)
        );
    }
}

void
kvms_derive(vm_space_t* vms) {
    pgtbl_walk(
        kernel_vms.pgtbl,
        kvms_derive_walker,
        NULL,
        (void*)vms->pgtbl
    );
}