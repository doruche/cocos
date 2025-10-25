#include "libs/printf.h"
#include "uspace/task.h"
#include "libs/panic.h"
#include "uspace/syscall.h"
#include "libs/elf.h"
#include "libs/string.h"
#include "libs/macros.h"
#include "task.h"

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
//         sys_task_gettid()
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
// 
//         usize npages = PGUP(p->p_filesz) / PAGE_SIZE;
//         vpn_t vpn = (vpn_t)PA2PN(PGDOWN(p->p_vaddr));
//         
// 
//         
//     }
// 
//     return 0;
// }

isize
main(void) {
    printf("Hello, World!\n");

    // try to launch an application
    // extern u8 __app_elf[];
    // isize tid = task_init_create("hello", __app_elf);
    // printf("pm: created task with tid %d\n", tid);

    return 0;
}