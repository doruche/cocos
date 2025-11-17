/*
 * risc-v page table management (sv39)
 */

#include "arch.h"
#include <libs/prelude.h>
#include <kernel/arch/pgtbl.h>
#include <kernel/arch/csr.h>
#include <kernel/arch/qemu-virt.h>
#include <kernel/arch/trap.h>
#include <kernel/mm/pm.h>

static void
pgtbl_init(arch_vm_t* vm) {
    for (usize i = 0; i < 512; i++) {
        vm->entries[i] = 0;
    }
}

static pte_t*
find_pte(arch_vm_t* vm, vpn_t vpn, bool alloc) {
    usize indices[3] = {
        (vpn >> 18) & 0x1FF,
        (vpn >> 9) & 0x1FF,
        vpn & 0x1FF
    };

    arch_vm_t* table = vm;
    for (usize level = 0; level < 3; level++) {
        pte_t* pte = &table->entries[indices[level]];
        if (level == 2) {
            return pte;
        }
        if (pte_is_branch(*pte)) {
            table = (arch_vm_t*)PTE2PA(*pte);
        } else if (alloc) {
            ppn_t new_table_ppn = unwrap_err(pm_alloc());
            memset((u8*)PN2PA(new_table_ppn), 0, PAGE_SIZE);
            pgtbl_init((arch_vm_t*)PN2PA(new_table_ppn));
            *pte = (new_table_ppn << 10) | PTE_V;
            table = (arch_vm_t*)PN2PA(new_table_ppn);
        } else {
            return NULL;
        }
    }
    unreachable()
}

vm_flags_t
pte_archflag2vmflag(u64 flags) {
    vm_flags_t vmflags = 0;
    if (flags & PTE_R) vmflags |= VM_READ;
    if (flags & PTE_W) vmflags |= VM_WRITE;
    if (flags & PTE_X) vmflags |= VM_EXEC;
    if (flags & PTE_U) vmflags |= VM_USER;
    assert((flags & PTE_ANON) == 0 || (flags & PTE_V) != 0); // anon mappings must be valid
    if (flags & PTE_ANON) vmflags |= VM_ANON;
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
    if (flags & VM_ANON) archflags |= PTE_ANON;
    assert((flags & VM_FAKE) == 0 || (archflags & PTE_V) != 0); // fake mappings cannot be valid
    if (flags & VM_FAKE) archflags &= ~PTE_V; // fake mapping means not valid

    return archflags;
}

void
arch_vm_map(
    arch_vm_t* vm, 
    vpn_t vpn, 
    ppn_t ppn, 
    vm_flags_t flags
) {
    pte_t* pte = unwrap_null(find_pte(vm, vpn, true));

    if (pte_is_mapped(*pte)) {
        panic("arch_vm_map: already mapped");
    }

    if (flags & VM_ANON) {
        // ppn will be ignored
        assert_eq(ppn, PPN_ANON);
        ppn = unwrap_err(pm_alloc());
    }

    u64 archflags = pte_vmflag2archflag(flags);

    *pte = (ppn << 10) | (archflags & 0x3FF);
}

void
arch_vm_unmap(arch_vm_t* vm, vpn_t vpn) {
    pte_t* pte = find_pte(vm, vpn, false);

    if (pte == NULL || !pte_is_mapped(*pte)) {
        panic("arch_vm_unmap: not mapped vpn %p", vpn);
    }

    if (pte_is_anonymous(*pte)) {
        ppn_t ppn = PTE2PPN(*pte);
        assert(pm_decref(ppn));
    }

    *pte = 0;
}

static void
freewalk(arch_vm_t* vm, usize level) {
    if (level >= 3) {
        unreachable();
    }

    for (usize i = 0; i < 512; i++) {
        pte_t* pte = &vm->entries[i];
        if (pte_is_branch(*pte)) {
            freewalk(
                (arch_vm_t*)PTE2PA(*pte),
                level + 1
            );
            // child page table has already been freed
        } else if (pte_is_leaf(*pte)) {
            if (pte_is_anonymous(*pte)) {
                ppn_t ppn = PTE2PPN(*pte);
                assert(pm_decref(ppn));
            }
        } else {
            // zero or invalid. if invalid, it must be a fake mapping, do nothing
            // currently only guard pages. let's do a simple sanity check.
            assert(*pte == 0 || PTE2PPN(*pte) == 0);
        }
        *pte = 0;
    }

    assert(pm_decref(PA2PN((paddr_t)vm)));
}

void
arch_vm_destroy(arch_vm_t *vm) {
    freewalk(vm, 0);
}

ppn_t
arch_vm_resolve(arch_vm_t* vm, vpn_t vpn) {
    pte_t* pte = find_pte(vm, vpn, false);
    if (pte == NULL || !pte_is_mapped(*pte)) {
        panic("arch_vm_resolve: not mapped vpn %p", vpn);
    }
    return PTE2PPN(*pte);
}

bool
arch_vm_is_mappable(arch_vm_t* vm, vpn_t vpn) {
    return !arch_vm_is_mapped(vm, vpn) &&
        (vpn < PA2PN(BIOS_BASE));
}

bool
arch_vm_is_mapped(arch_vm_t* vm, vpn_t vpn) {
    pte_t* pte = find_pte(vm, vpn, false);
    return pte != NULL && pte_is_mapped(*pte);
}

void
arch_vm_flush_tlb(void) {
    flush_tlb();
}

void
arch_vm_activate(arch_vm_t* vm) {
    arch_vm_flush_tlb();
    w_satp(SATP(vm));
}

arch_vm_t kvm __aligned(PAGE_SIZE) = {0};

static void
map_region(
    arch_vm_t* vm, 
    kaddr_t start, 
    kaddr_t end,
    vm_flags_t flags
) {
    usize npages = PGUP(end - start) / PAGE_SIZE;
    vpn_t pn = PA2PN(start);
    for (usize i = 0; i < npages; i++) {
        arch_vm_map(
            vm,
            pn + i,
            pn + i,
            flags
        );
    }
    pr_trace("mapped region: [0x%lx, 0x%lx) flags=%c%c%c%c",
        start, end,
        (flags & VM_READ) ? 'r' : '-',
        (flags & VM_WRITE) ? 'w' : '-',
        (flags & VM_EXEC) ? 'x' : '-',
        (flags & VM_USER) ? 'u' : '-'
    );
}

void
make_kvm(arch_vm_t* vm) {
    extern u8 __stext[];
    extern u8 __etext[];
    extern u8 __srodata[];
    extern u8 __erodata[];
    extern u8 __sdata[];
    extern u8 __edata[];
    extern u8 __sbss[];
    extern u8 __ebss[];
    extern u8 __stack0_bottom[];
    extern u8 __stack0_top[];
    extern u8 __smem[];

    map_region(
        vm,
        (kaddr_t)__stext,
        (kaddr_t)__etext,
        VM_READ | VM_EXEC
    );
    map_region(
        vm,
        (kaddr_t)__srodata,
        (kaddr_t)__erodata,
        VM_READ
    );
    map_region(
        vm,
        (kaddr_t)__sdata,
        (kaddr_t)__edata,
        VM_READ | VM_WRITE
    );
    map_region(
        vm,
        (kaddr_t)__sbss,
        (kaddr_t)__ebss,
        VM_READ | VM_WRITE
    );
    map_region(
        vm,
        (kaddr_t)__stack0_bottom,
        (kaddr_t)__stack0_top,
        VM_READ | VM_WRITE
    );
    map_region(
        vm,
        (kaddr_t)__smem,
        (kaddr_t)PHYSTOP,
        VM_READ | VM_WRITE
    );
    map_region(
        vm,
        (kaddr_t)PLIC,
        (kaddr_t)(PLIC + PLIC_RANGE),
        VM_READ | VM_WRITE
    );

    arch_vm_map(
        vm,
        PA2PN(TRAMPOLINE),
        PA2PN((kaddr_t)u_trampoline_entry),
        VM_READ | VM_EXEC
    );
}

void
arch_vm_deactivate(void) {
    flush_tlb();
    arch_vm_activate(&kvm);
}

arch_vm_t*
arch_vm_creat(void) {
    arch_vm_t* vm = (arch_vm_t*)PN2PA(unwrap_err(pm_alloc()));
    memset(vm, 0, sizeof(arch_vm_t));
    /* 
     * to manage kernel and user vm spaces, we adopt a simple strategy:
     * 1. kernel space is static, we map all the memory regions at once during boot
     * 2. user space is cloned from kernel space at initialization,
     *  then mapped on demand during runtime.
     * must notice that kernel only handles kernel space mappings,
     * user space mappings must be handled by pm and pager server.
     */
    make_kvm(vm);

    return vm;
}

vpn_t
arch_vm_topaddr(void) {
    return PA2PN(TRAMPOLINE);
}

vpn_t
arch_vm_kbase(void) {
    return PA2PN(BIOS_BASE);
}

void
arch_kvm_init(void) {
    make_kvm(&kvm);
    arch_vm_activate(&kvm);
}
