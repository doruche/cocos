/*
 * address space management
 */
#pragma once

#include <libs/prelude.h>
#include <libs/list.h>
#include <kernel/arch/arch.h>
#include <kernel/task/sched.h>

typedef struct _addr_space_t {
    arch_vm_t* arch_vm;
    asid_t id __readonly;
    usize rc;
    // node in global as list
    list_elem_t node;
} addr_space_t;

void        as_init(void);


typedef struct _task_t task_t; // workaround circular dependency
addr_space_t*  as_creat(task_t* owner);
result_t    as_get(asid_t asid, addr_space_t** out);
result_t    as_bind(addr_space_t* as, task_t* task);
result_t    as_unbind(addr_space_t* as, task_t* task);
result_t    as_map(
    addr_space_t* as, 
    vpn_t vpn, 
    ppn_t ppn,
    usize npages,
    vm_flags_t flags
);
result_t    as_unmap(
    addr_space_t* as,
    vpn_t vpn, 
    usize npages
);
result_t    as_memcheck(
    addr_space_t* as,
    vaddr_t addr,
    usize len
);
result_t    as_memcpy(
    addr_space_t* as,
    vaddr_t dst,
    const u8* src,
    usize len
);
result_t    as_memset(
    addr_space_t* as,
    vaddr_t dst,
    u8 val,
    usize len
);

bool        as_is_mapped(addr_space_t* as, vpn_t vpn);

void        as_dump(addr_space_t* as);
