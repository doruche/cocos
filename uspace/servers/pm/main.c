#include "uspace/task.h"
#include "uspace/syscall.h"
#include "libs/elf.h"
#include "libs/string.h"
#include "task.h"
#include "libs/prelude.h"

isize
main(void) {
    printf("Hello, World!\n");

    // try to launch an application
    extern u8 __app_elf[];
    tid_t tid = hot_spawn("app", __app_elf);
    if (tid == TID_INVALID) {
        panic("pm: failed to create task");
    }
    trace("pm: launched app with tid %d", tid);

    loop {}

    return 0;
}