#pragma once

#include <libs/prelude.h>

/* assembly declarations */
void    ktrap_trampoline(void);
void    u_trampoline_entry(void);
void    u_trampoline_ret(void);

u64     ktrap(u64 prev_sp);
void    utrap(void);
