#pragma once

#include "libs/prelude.h"

isize   vm_memcpy(
    tid_t tid,
    vaddr_t dst,
    const u8* src,
    usize len
);

isize   vm_memset(
    tid_t tid,
    vaddr_t dst,
    u8 value,
    usize len
);