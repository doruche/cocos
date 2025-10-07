#ifndef _K_TRAP_H
#define _K_TRAP_H 1

#include "libs/types.h"

// typedef struct _trapframe_t {
//     u64 x[32];
//     u64 sstatus;
//     u64 sepc;
// } trapframe_t;

extern
void    ktrap_trampoline(void);
u64     ktrap(u64 prev_sp);

#endif