#include "../arch.h"
#include <libs/prelude.h>

u64
arch_syscall_arg(
    arch_trapframe_t* tf,
    usize idx
) {
    assert(idx < 5);
    return tf->x[idx + 10];
}

void
arch_store_syscall_ret(
    arch_trapframe_t* tf,
    isize ret
) {
    tf->x[10] = (u64)ret;
}

void
arch_set_pc(
    arch_trapframe_t* tf,
    uaddr_t pc
) {
    tf->sepc = pc;
}
