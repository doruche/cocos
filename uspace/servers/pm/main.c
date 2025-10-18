#include "libs/types.h"
#include "uspace/syscall.h"
#include "libs/macros.h"

char* hello = "Hello, World from PM Server!\n";

void
_start(void) {
    sys_puts(hello);
    sys_kill(sys_gettid());
}