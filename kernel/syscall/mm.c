#include "libs/sysno.h"
#include "kernel/task/sched.h"
#include "kernel/syscall.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "libs/types.h"
#include "kernel/mm/vm.h"

SYSCALL_DEFINE1(pm_alloc, tid_t, tid) {
    task_t* current = unwrap_null(current_task);
    trace("sys_pm_alloc: task %d allocating a physical page for task %d",
        current->tid,
        tid
    );
    task_t* target_task = task_get(tid);
    if (target_task == NULL) {
        trace("sys_pm_alloc: target task %d not found", tid);
        return -ERR_NOENT;
    }
    ppn_t ppn = pm_alloc();
    if ((isize)ppn < 0) {
        trace("sys_pm_alloc: pm_alloc error %s",
            strerr((isize)ppn)
        );
        return (isize)ppn;
    }

    for (usize i = 0; i < TASK_MAX_PHYS_PAGES; i++) {
        if (target_task->alloced_pages[i] == 0) {
            target_task->alloced_pages[i] = ppn;
            trace("sys_pm_alloc: allocated ppn 0x%lx for task %d",
                ppn,
                tid
            );
            return (isize)ppn;
        }
    }

    // no space
    trace("sys_pm_alloc: no space to track allocated page for task %d",
        tid
    );
    assert(pm_decref(ppn));

    return -ERR_NOMEM;
}

SYSCALL_DEFINE3(
    vm_unmap,
    tid_t, tid,
    vpn_t, vpn,
    usize, npages
) {
    task_t* current = unwrap_null(current_task);
    trace("sys_vm_unmap: task %d unmapping vpn 0x%lx, npages %ld for task %d",
        current->tid,
        vpn,
        npages,
        tid
    ); 

    task_t* target_task = task_get(tid);
    if (target_task == NULL) {
        trace("sys_vm_unmap: target task %d not found", tid);
        return -ERR_NOENT;
    }

    for (usize i = 0; i < npages; i++) {
        if (!vm_is_mapped(
            target_task->vms,
            vpn + i
        )) {
            trace("sys_vm_unmap: vpn 0x%lx not mapped in task %d",
                vpn + i,
                tid
            );
            return -ERR_FAULT;
        }
    }

    vm_unmap(
        target_task->vms,
        vpn,
        npages
    );

    return 0;
}

SYSCALL_DEFINE5(
    vm_map,
    tid_t, tid,
    vpn_t, vpn,
    ppn_t, ppn,
    usize, npages,
    vm_flags_t, flags
) {
    task_t* current = unwrap_null(current_task);
    trace("sys_vm_map: task %d mapping ppn 0x%lx to vpn 0x%lx, npages %ld for task %d with flags 0x%03lx",
        current->tid,
        ppn,
        vpn,
        npages,
        tid,
        flags
    ); 

    task_t* target_task = task_get(tid);
    if (target_task == NULL) {
        trace("sys_vm_map: target task %d not found", tid);
        return -ERR_NOENT;
    }

    for (usize i = 0; i < npages; i++) {
        if (vm_is_mapped(
            target_task->vms,
            vpn + i
        )) {
            trace("sys_vm_map: vpn 0x%lx already mapped in task %d",
                vpn + i,
                tid
            );
            return -ERR_EXIST;
        }
    }

    vm_map(
        target_task->vms,
        vpn,
        ppn,
        npages,
        flags
    );

    return 0;
}