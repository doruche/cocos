#include "arch/panic.h"
#include "arch/sbi.h"

void
panic(const char* msg) {
    sbi_console_puts("panic: ");
    sbi_console_puts(msg);
    sbi_console_puts("\n");
    sbi_shutdown();
    for(;;) {
        ;
    }
}