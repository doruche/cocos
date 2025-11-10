#include <libs/prelude.h>
#include <kernel/arch/arch.h>
#include <kernel/task/processor.h>
#include <kernel/task/sched.h>

processor_t processor;

void
processor_init(void) {
    processor.cur_task = NULL;
    extern arch_kctx_t sched_ctx;
    processor.sched_ctx = &sched_ctx;

    // reuse boot stack for scheduler
    extern u8 __stack0_top[];

    arch_kctx_init(
        processor.sched_ctx,
        (kaddr_t)scheduler,
        (vpn_t)PA2PN((kaddr_t)__stack0_top)
    );
}
