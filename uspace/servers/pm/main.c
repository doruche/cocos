#include "libs/printf.h"
#include "uspace/task.h"
#include "libs/panic.h"
#include "uspace/syscall.h"
#include "libs/elf.h"
#include "libs/string.h"
#include "libs/macros.h"
#include "task.h"
#include "libs/types.h"
#include "libs/log.h"
#include "libs/assert.h"

// static tid_t
// task_init_create(
//     const char* name,
//     u8* elf_data
// ) {
//     elf_hdr_t* elf_hdr = (elf_hdr_t*)elf_data;
//     if (memcmp(elf_hdr->e_ident, ELF_MAGIC, 4) != 0) {
//         printf("pm: invalid elf magic\n");
//         return -1;
//     }
//     tid_t tid = sys_task_spawn(
//         name,
//         (uaddr_t)(elf_hdr->e_entry),
//         task_gettid()
//     );
// 
//     elf_phdr_t* phdr = (elf_phdr_t*)(elf_data + elf_hdr->e_phoff);
//     extern u8 __sheap[];
//     vpn_t tmp_access_page = (vpn_t)PA2PN((u64)__sheap);
//     for (usize i = 0; i < elf_hdr->e_phnum; i++) {
//         elf_phdr_t* p = &phdr[i];
//         if (p->p_type != PT_LOAD) {
//             continue;
//         }
//         vm_flags_t flags = 0;
//         if (p->p_flags & PF_R) {
//             flags |= VM_READ;
//         }
//         if (p->p_flags & PF_W) {
//             flags |= VM_WRITE;
//         }
//         if (p->p_flags & PF_X) {
//             flags |= VM_EXEC;
//         }
//      
//         
//     }
//     printf("pm: loaded elf for task %d\n", tid);
//     return 0;
// }

isize
main(void) {
    printf("Hello, World!\n");

    // try to launch an application
    extern u8 __app_elf[];
    tid_t tid = hot_spawn("app", __app_elf);
    if (tid == TID_INVALID) {
        panic("pm: failed to create task");
    }

    usize counter = 0;

    loop  {
        // printf("pm: running... %d\n", counter++);
        trace("pm: running... %d", counter++);
        info("pm: running... %d", counter);
        assert_eq(1, 1);
        task_yield();
    }

    return 0;
}