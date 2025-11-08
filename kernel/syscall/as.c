#include <libs/prelude.h>
#include <kernel/task/sched.h>
#include <kernel/syscall.h>
#include <kernel/mm/as.h>


SYSCALL_DEFINE1(as_get, tid_t, tid) {
    task_t* task = NULL;
    result_t ret = task_get(tid, &task);
    if (is_err(ret)) {
        warn("sys_as_get: failed to get task %ld: %s",
            tid, strerr(ret));
        return ret;
    }
    trace("sys_as_get: got addr space %ld of task tid=%ld name=%s",
        task->as->id,
        task->tid, task->name);
    return task->as->id;
}

SYSCALL_DEFINE5(
    as_map,
    asid_t, asid,
    vpn_t, vpn,
    ppn_t, ppn,
    usize, npages,
    vm_flags_t, flags
) {
    addr_space_t* as;
    result_t ret = as_get(asid, &as);
    if (is_err(ret)) {
        warn("sys_as_map: failed to get addr space %ld: %s", 
            asid, strerr(ret));
        return ret;
    }

    ret = as_map(as, vpn, ppn, npages, flags);
    if (is_err(ret)) {
        warn("sys_as_map: failed to map %ld pages at vpn %lx in as %ld: %s",
            npages, vpn, asid, strerr(ret));
        return ret;
    }

    trace("sys_as_map: successfully mapped %ld pages at vpn %lx in as %ld",
        npages, vpn, asid);
    return 0;
}

SYSCALL_DEFINE3(
    as_unmap,
    asid_t, asid,
    vpn_t, vpn,
    usize, npages
) {
    addr_space_t* as;
    result_t ret = as_get(asid, &as);
    if (is_err(ret)) {
        warn("sys_as_unmap: failed to get addr space %ld: %s", 
            asid, strerr(ret));
        return ret;
    }

    ret = as_unmap(as, vpn, npages);
    if (is_err(ret)) {
        warn("sys_as_unmap: failed to unmap %ld pages at vpn %lx in as %ld: %s",
            npages, vpn, asid, strerr(ret));
        return ret;
    }

    trace("sys_as_unmap: successfully unmapped %ld pages at vpn %lx in as %ld",
        npages, vpn, asid);
    return 0;
}

SYSCALL_DEFINE4(
    as_write,
    asid_t, asid,
    vaddr_t, addr,
    const u8*, buf,
    usize, len
) {
    addr_space_t* as;
    result_t ret = as_get(asid, &as);
    if (is_err(ret)) {
        warn("sys_as_write: failed to get addr space %ld: %s", 
            asid, strerr(ret));
        return ret;
    }
    ret = as_memcpy(as, addr, buf, len);
    if (is_err(ret)) {
        warn("sys_as_write: failed to write 0x%lx bytes to addr 0x%lx in as %ld: %s",
            len, addr, asid, strerr(ret));
        return ret;
    }
    trace("sys_as_write: successfully wrote 0x%lx bytes to addr 0x%lx in as %ld",
        len, addr, asid);
    return OK;
}
