#include "task.h"
#include <libs/prelude.h>
#include <libs/elf.h>
#include <libs/iter.h>
#include <uspace/task.h>
#include <uspace/syscall.h>

static struct task_t tasks[MAX_TASK_NUM];

void
task_init(void) {
    for (usize i = 0; i < MAX_TASK_NUM; i++) {
        tasks[i].in_use = false;
        tasks[i].tid = TID_INVALID;
        tasks[i].brk = 0;
    }
}

result_t
task_alloc(struct task_t** out_task) {
    for (usize i = 0; i < MAX_TASK_NUM; i++) {
        if (!tasks[i].in_use) {
            tasks[i].in_use = true;
            *out_task = &tasks[i];
            pr_info("task_alloc: allocated task slot %ld",
                i);
            return OK;
        }
    }
    pr_warn("task_alloc: no free task slot available");
    return -ERR_NOMEM;
}

result_t
task_get(tid_t tid, struct task_t** out_task) {
    for (usize i = 0; i < MAX_TASK_NUM; i++) {
        if (tasks[i].tid == tid) {
            assert(tasks[i].in_use);
            *out_task = &tasks[i];
            return OK;
        }
    }
    return -ERR_NOENT;
}

result_t
task_free(tid_t tid) {
    struct task_t* task = NULL;
    result_t ret = task_get(tid, &task);
    if (is_err(ret)) {
        return ret;
    }
    assert(task->in_use);
    pr_info("task_free: freeing task tid %ld name %s slot %ld",
        task->tid, task->name, task - tasks);
    task->in_use = false;
    task->tid = TID_INVALID;
    return OK;
}

static vm_flags_t
pflags2vmflags(usize p_flags) {
    vm_flags_t vm_flags = 0;
    if (p_flags & PF_R) {
        vm_flags |= VM_READ;
    }
    if (p_flags & PF_W) {
        vm_flags |= VM_WRITE;
    }
    if (p_flags & PF_X) {
        vm_flags |= VM_EXEC;
    }
    return vm_flags;
}

result_t
proc_spawn(
    const char* name,
    const u8* elf,
    tid_t* out_tid
) {
    struct task_t* task = NULL;
    result_t ret = task_alloc(&task);
    if (is_err(ret)) {
        goto err;
    }

    elf_hdr_t* elf_hdr = (elf_hdr_t*)elf;
    if (memcmp(elf_hdr->e_ident, ELF_MAGIC, 4) != 0) {
        pr_warn("proc_spawn: invalid elf magic");
        ret = -ERR_INVAL;
        goto err;
    }

    tid_t tid = sys_task_spawn(
        name,
        elf_hdr->e_entry,
        ASID_NEW
    );
    if (is_err(tid)) {
        pr_warn("proc_spawn: sys_task_spawn failed: %s",
            strerr(tid));
        ret = tid;
        goto err;
    }

    asid_t asid = unwrap_err(sys_as_get(tid));

    for (usize i = 0; i < elf_hdr->e_phnum; i++) {
        elf_phdr_t* phdr = (elf_phdr_t*)(elf + 
            elf_hdr->e_phoff + i * sizeof(elf_phdr_t));
        if (phdr->p_type != PT_LOAD) {
            continue;
        }

        vm_flags_t flags = VM_USER | VM_ANON | 
            pflags2vmflags(phdr->p_flags);

        ret = sys_as_map(
            asid,
            PA2PN(phdr->p_vaddr),
            PPN_ANON,
            PGUP(phdr->p_memsz) / PAGE_SIZE,
            flags
        );
        task->brk = max(
            task->brk,
            PA2PN(phdr->p_vaddr + phdr->p_memsz)
        );

        if (is_err(ret)) {
            pr_warn("proc_spawn: sys_as_map failed: %s",
                strerr(ret));
            goto err;            
        }

        // write segment data
        ret = sys_as_memcpy(
            asid,
            phdr->p_vaddr,
            elf + phdr->p_offset,
            phdr->p_filesz
        );
        if (is_err(ret)) {
            pr_warn("proc_spawn: sys_as_memcpy failed: %s",
                strerr(ret));
            goto err;
        }
        ret = sys_as_memset(
            asid,
            phdr->p_vaddr + phdr->p_filesz,
            0,
            phdr->p_memsz - phdr->p_filesz
        );
        if (is_err(ret)) {
            pr_warn("proc_spawn: sys_as_memset failed: %s",
                strerr(ret));
            goto err;
        }
    }

    task->tid = tid;
    task->asid = asid;
    task->brk++;
    strncpy(task->name, name, TASK_NAME_MAX_LEN);
    task->name[TASK_NAME_MAX_LEN - 1] = '\0';

    unwrap_err(sys_task_resume(tid));
    *out_tid = tid;
    pr_info("proc_spawn: spawned process '%s' (tid %ld)",
        name, tid);
    return OK;

err:
    if (task != NULL) {
        task_free(task->tid);
    }
    return ret;
}

result_t
vm_map_anon(
    tid_t tid,
    usize npages,
    vpn_t* out
) {
    struct task_t* task = NULL;
    result_t ret = task_get(tid, &task);
    if (is_err(ret)) {
        return ret;
    }

    ret = sys_as_map(
        task->asid,
        task->brk,
        PPN_ANON,
        npages,
        VM_USER | VM_ANON | VM_READ | VM_WRITE
    );
    if (is_err(ret)) {
        pr_warn("vm_map_anon: sys_as_map failed: %s",
            strerr(ret));
        return ret;
    }
    *out = task->brk;
    task->brk += npages;

    return OK;
}

result_t
vm_map_mmio(
    tid_t tid,
    ppn_t ppn,
    usize npages,
    vpn_t* out
) {
    struct task_t* task = NULL;
    result_t ret = task_get(tid, &task);
    if (is_err(ret)) {
        return ret;
    }

    ret = sys_as_map(
        task->asid,
        task->brk,
        ppn,
        npages,
        VM_USER | VM_READ | VM_WRITE
    );
    if (is_err(ret)) {
        pr_warn("vm_map_mmio: sys_as_map failed: %s",
            strerr(ret));
        return ret;
    }
    *out = task->brk;
    task->brk += npages;

    return OK;
}

result_t
vm_unmap(
    tid_t tid,
    vpn_t vpn,
    usize npages
) {
    struct task_t* task = NULL;
    result_t ret = task_get(tid, &task);
    if (is_err(ret)) {
        return ret;
    }

    ret = sys_as_unmap(
        task->asid,
        vpn,
        npages
    );
    if (is_err(ret)) {
        pr_warn("vm_unmap: sys_as_unmap failed: %s",
            strerr(ret));
        return ret;
    }

    return OK;
}
