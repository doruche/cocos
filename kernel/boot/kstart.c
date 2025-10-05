#include "arch/layout.h"
#include "arch/sbi.h"

void
kstart(void) {
    sbi_console_puts("arrive at kstart\n");
    sbi_shutdown();
}