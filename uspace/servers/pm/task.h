#pragma once

#include <libs/prelude.h>


result_t
proc_spawn(
    const char* name,
    const u8* elf,
    tid_t* out_tid
);
