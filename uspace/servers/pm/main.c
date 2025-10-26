#include "libs/printf.h"
#include "uspace/task.h"
#include "libs/panic.h"
#include "uspace/syscall.h"
#include "libs/elf.h"
#include "libs/string.h"

#include "task.h"
#include "libs/prelude.h"
#include "libs/log.h"
#include "libs/assert.h"

isize
main(void) {
    printf("Hello, World!\n");

    // try to launch an application
    extern u8 __app_elf[];
    tid_t tid = hot_spawn("app", __app_elf);
    if (tid == TID_INVALID) {
        panic("pm: failed to create task");
    }

    usize counter = 0;

    loop  {
        trace("pm: running... %d", counter++);
        info("pm: running... %d", counter);
        assert_eq(1, 1);
        task_yield();
    }

    return 0;
}