#include "kernel/misc/printk.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"

#include "kernel/arch/timer.h"
#include "kernel/arch/csr.h"

void
kstart(void) {
    extern char __stext[], __etext[];
    extern char __srodata[], __erodata[];
    extern char __sdata[], __edata[];
    extern char __sbss[], __ebss[];

    info("cocos booting...");
    trace(".text: [%p, %p)", __stext, __etext);
    trace(".rodata: [%p, %p)", __srodata, __erodata);
    trace(".data: [%p, %p)", __sdata, __edata);
    trace(".bss: [%p, %p)", __sbss, __ebss);

    #include "kernel/trap.h"
    w_stvec(STVEC((u64)ktrap_trampoline, STVEC_MODE_DIRECT));
    enable_intr();
    timer_init();

    for(;;);

    unreachable()
}