#include "libs/prelude.h"
#include "uspace/task.h"
#include "vm.h"
#include "task.h"
#include "libs/log.h"
#include "libs/assert.h"
#include "libs/elf.h"
#include "libs/string.h"
#include "uspace/syscall.h"
#include "libs/iter.h"

static __aligned(PAGE_SIZE) u8 page_buf[PAGE_SIZE];

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

static isize
hot_spawn_callback(
    const range_t* range,
    void* ctx
) {
    trace("hot_spawn_callback: range 0x%lx - 0x%lx",
        range->start,
        range->end
    );

    struct {
        tid_t tid;
        elf_phdr_t* phdr;
        u8* elf_data;
        bool zero_fill;
    }* state = ctx;

    usize elf_off = range->start - state->phdr->p_vaddr + state->phdr->p_offset;
    usize page_off = range->start - align_down(range->start, PAGE_SIZE);
    usize len = range->end - range->start;
    assert(len <= PAGE_SIZE);

    unwrap_err(
        sys_vm_unmap(
            task_gettid(),
            PA2PN((vaddr_t)page_buf),
            1
        )
    );
    ppn_t ppn = unwrap_err(sys_pm_alloc(state->tid));
    unwrap_err(
        sys_vm_map(
            task_gettid(),
            PA2PN((vaddr_t)page_buf),
            ppn,
            1,
            VM_READ | VM_WRITE
        )
    );
    vm_flags_t flags = pflags2vmflags(state->phdr->p_flags);
    if (state->zero_fill) {
        memset(page_buf + page_off, 0, len);
    } else {
        memcpy(page_buf + page_off, state->elf_data + elf_off, len);
    }
    unwrap_err(
        sys_vm_map(
            state->tid,
            PA2PN(range->start),
            ppn,
            1,
            flags
        )
    );

    return 0;
}

tid_t
hot_spawn(const char* name, u8* elf_data) {
    elf_hdr_t* elf_hdr = (elf_hdr_t*)elf_data;
    if (memcmp(elf_hdr->e_ident, ELF_MAGIC, 4) != 0) {
        warn("hot_spawn: invalid ELF magic");
        return TID_INVALID;
    }    
    tid_t tid = sys_task_spawn(
        name,
        elf_hdr->e_entry,
        task_gettid() // identical to TID_PM
    );
    if (is_err(tid)) {
        warn("hot_spawn: sys_task_spawn failed");
        return TID_INVALID;
    }

    elf_phdr_t* phdrs = (elf_phdr_t*)(elf_data + elf_hdr->e_phoff);

    for (usize i = 0; i < elf_hdr->e_phnum; i++) {
        elf_phdr_t* phdr = &phdrs[i];
        if (phdr->p_type != PT_LOAD) {
            continue;
        }
        unwrap_err(
            range_iter(
                &(range_t){
                    .start = phdr->p_vaddr,
                    .end = phdr->p_vaddr + phdr->p_filesz
                },
                PAGE_SIZE,
                hot_spawn_callback,
                &(struct {
                    tid_t tid;
                    elf_phdr_t* phdr;
                    u8* elf_data;
                    bool zero_fill;
                }){
                    .tid = tid,
                    .phdr = phdr,
                    .elf_data = elf_data,
                    .zero_fill = false,
                }
            )
        );
        unwrap_err(
            range_iter(
                &(range_t){
                    .start = phdr->p_vaddr + phdr->p_filesz,
                    .end = phdr->p_vaddr + phdr->p_memsz
                },
                PAGE_SIZE,
                hot_spawn_callback,
                &(struct {
                    tid_t tid;
                    elf_phdr_t* phdr;
                    u8* elf_data;
                    bool zero_fill;
                }){
                    .tid = tid,
                    .phdr = phdr,
                    .elf_data = elf_data,
                    .zero_fill = true,
                }
            )
        );
    }

    info("hot_spawn: spawned task %d", tid);
    return tid;
}