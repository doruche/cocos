#include <task.h>
#include <libs/prelude.h>
#include <libs/elf.h>
#include <libs/iter.h>
#include <uspace/task.h>
#include <uspace/syscall.h>

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
    elf_hdr_t* elf_hdr = (elf_hdr_t*)elf;
    if (memcmp(elf_hdr->e_ident, ELF_MAGIC, 4) != 0) {
        warn("proc_spawn: invalid elf magic");
        return -ERR_INVAL;
    }

    tid_t tid = sys_task_spawn(
        name,
        elf_hdr->e_entry,
        ASID_NEW
    );
    if (is_err(tid)) {
        warn("proc_spawn: sys_task_spawn failed: %s",
            strerr(tid));
        return tid;
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

        result_t ret = sys_as_map(
            asid,
            PA2PN(phdr->p_vaddr),
            PPN_ANON,
            PGUP(phdr->p_memsz) / PAGE_SIZE,
            flags
        );

        if (is_err(ret)) {
            warn("proc_spawn: sys_as_map failed: %s",
                strerr(ret));
            return ret;
        }

        // write segment data
        ret = sys_as_write(
            asid,
            phdr->p_vaddr,
            elf + phdr->p_offset,
            phdr->p_filesz
        );
        if (is_err(ret)) {
            warn("proc_spawn: sys_as_write failed: %s",
                strerr(ret));
            return ret;
        }
    }

    unwrap_err(sys_task_resume(tid));
    *out_tid = tid;
    info("proc_spawn: spawned process '%s' (tid %ld)",
        name, tid);
    return OK;
}
