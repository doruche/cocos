#include <libs/prelude.h>
#include <libs/list.h>
#include <libs/iter.h>
#include <kernel/arch/arch.h>
#include <kernel/task/sched.h>
#include <kernel/mm/as.h>
#include <kernel/mm/pm.h>
#include <kernel/mm/slab.h>

list_t as_list;
kmem_cache_t as_cache;

static asid_t next_asid = 1;

static asid_t
alloc_asid() {
    return next_asid++;
}

void
as_init(void) {
    list_init(&as_list);
    kmem_cache_create(&as_cache, "addr_space", sizeof(addr_space_t));
}

result_t
as_get(asid_t asid, addr_space_t** out) {
    list_foreach(iter, &as_list) {
        addr_space_t* as = list_entry(iter, addr_space_t, node);
        if (as->id == asid) {
            *out = as;
            return OK;
        }
    }
    return -ERR_NOT_FOUND;
}

addr_space_t*
as_creat(task_t* owner) {
    addr_space_t* as = unwrap_null(kmem_cache_alloc(&as_cache));
    memset(as, 0, sizeof(addr_space_t));
    as->arch_vm = arch_vm_creat();
    as->id = alloc_asid();
    as->rc = 0;
    list_push_back(&as_list, &as->node);
    
    unwrap_err(as_bind(as, owner));

    pr_trace("as_creat: created address space %ld", as->id);
    return as;
}

result_t
as_bind(addr_space_t* as, task_t* task) {
    assert(task->as == NULL);
    if (task->as != NULL) {
        return -ERR_EXIST;
    }
    task->as = as;
    as->rc++;
    pr_trace("as_bind: bound address space %ld to task %ld, rc=%ld",
        as->id, task->tid, as->rc);
    return OK;
}

/*
 * this function is called when alive is true and rc == 0
 */
static void
as_destroy(addr_space_t* as) {
    assert(as->rc == 0);
    list_remove(&as->node);
    pr_trace("as_destroy: destroying address space %ld", as->id);
    arch_vm_destroy(as->arch_vm);
    kmem_cache_free(&as_cache, as);
}

result_t
as_unbind(addr_space_t* as, task_t* task) {
    if (task->as != as) {
        return -ERR_MISSMATCH;
    }
    task->as = NULL;
    assert(as->rc > 0);
    as->rc--;
    pr_trace("as_unbind: unbound address space %ld from task %ld, rc=%ld",
        as->id, task->tid, as->rc);

    if (as->rc == 0) {
        pr_trace("as_unbind: address space %ld rc is 0, destroying it", as->id);
        as_destroy(as);
    }
    
    return OK;
}

result_t
as_map(
    addr_space_t* as, 
    vpn_t vpn, 
    ppn_t ppn,
    usize npages,
    vm_flags_t flags
) {
    if (npages == 0) {
        pr_warn("as_map: npages is 0");
        return OK;
    }
    for (usize i = 0; i < npages; i++) {
        if (arch_vm_is_mapped(as->arch_vm, vpn + i)) {
            pr_warn("as_map: vpn 0x%lx is already mapped", vpn + i);
            return -ERR_EXIST;
        }
    }

    for (usize i = 0; i < npages; i++) {
        arch_vm_map(
            as->arch_vm,
            vpn + i,
            flags & VM_ANON ? PPN_ANON : ppn + i,
            flags
        );
    }

    pr_trace("as_map: mapped ppn [0x%lx, 0x%lx) to vpn [0x%lx, 0x%lx), flags 0x%x",
        ppn,
        ppn + npages,
        vpn,
        vpn + npages,
        flags
    );

    return OK;
}

result_t
as_unmap(
    addr_space_t* as, 
    vpn_t vpn, 
    usize npages
) {
    if (npages == 0) {
        pr_warn("as_unmap: npages is 0");
        return OK;
    }
    for (usize i = 0; i < npages; i++) {
        if (!arch_vm_is_mapped(as->arch_vm, vpn + i)) {
            pr_warn("as_unmap: vpn 0x%lx is not mapped", vpn + i);
            return -ERR_NOT_FOUND;
        }
    }

    for (usize i = 0; i < npages; i++) {
        arch_vm_unmap(as->arch_vm, vpn + i);
    }

    pr_trace("as_unmap: unmapped vpn [0x%lx, 0x%lx)",
        vpn,
        vpn + npages
    );
    return OK;
}

static result_t
as_memcheck_callback(
    const range_t* chunk,
    void* ctx
) {
    addr_space_t* as = ctx;
    if (!arch_vm_is_mapped(as->arch_vm, PA2PN(chunk->start))) {
        pr_warn("as_memcheck: unmapped vpn %lx", PA2PN(chunk->start));
        return -ERR_FAULT;
    }
    return OK;
}

result_t
as_memcheck(
    addr_space_t* as,
    vaddr_t addr,
    usize len
) {
    return range_iter(
        &(range_t) {
            .start = addr,
            .end = addr + len,
        },
        PAGE_SIZE,
        as_memcheck_callback,
        as
    );
}

static result_t
as_memcpy_callback(
    const range_t* chunk,
    void* ctx
) {
    struct {
        const u8* src;
        addr_space_t* as;
    } *state = ctx;
    ppn_t ppn = arch_vm_resolve(state->as->arch_vm, PA2PN(chunk->start));
    usize inpage_offset = chunk->start % PAGE_SIZE;
    usize inpage_len = chunk->end - chunk->start;
    memcpy(
        (void*)(PN2PA(ppn) + inpage_offset),
        (const void*)state->src,
        inpage_len
    );
    state->src += inpage_len;

    return OK;
}

result_t as_memcpy(
    addr_space_t* as,
    vaddr_t dst,
    const u8* src,
    usize len
) {
    if (is_err(as_memcheck(as, dst, len))) {
        pr_warn("as_memcpy: memory check failed for dst 0x%lx, len %ld", dst, len);
        return -ERR_FAULT;
    }

    unwrap_err(range_iter(
        &(range_t) {
            .start = dst,
            .end = dst + len,
        },
        PAGE_SIZE,
        as_memcpy_callback,
        &(struct {
            const u8* src;
            addr_space_t* as;
        }) {
            .src = src,
            .as = as,
        }
    ));

    return OK;
}

static result_t
as_memset_callback(
    const range_t* chunk,
    void* ctx
) {
    struct {
        u8 val;
        addr_space_t* as;
    } *state = ctx;
    ppn_t ppn = arch_vm_resolve(state->as->arch_vm, PA2PN(chunk->start));
    usize inpage_offset = chunk->start % PAGE_SIZE;
    usize inpage_len = chunk->end - chunk->start;
    memset(
        (void*)(PN2PA(ppn) + inpage_offset),
        state->val,
        inpage_len
    );

    return OK;
}

result_t
as_memset(
    addr_space_t* as,
    vaddr_t dst,
    u8 value,
    usize len
) {
    if (is_err(as_memcheck(as, dst, len))) {
        pr_warn("as_memset: memory check failed for dst 0x%lx, len %ld", dst, len);
        return -ERR_FAULT;
    }

    return unwrap_err(range_iter(
        &(range_t) {
            .start = dst,
            .end = dst + len,
        },
        PAGE_SIZE,
        as_memset_callback,
        &(struct {
            u8 val;
            addr_space_t* as;
        }) {
            .val = value,
            .as = as,
        }
    ));

    return OK;
}

