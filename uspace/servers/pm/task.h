#pragma once

#include <libs/prelude.h>

// spawn a task with fully initialized vm space
// does not need a pager
tid_t   hot_spawn(
    const char* name,
    u8* elf_data
);

// spawn a task without initialized vm space
// needs a pager to handle page faults
tid_t   cold_spawn(
    const char* name,
    u8* elf_data,
    tid_t pager
);