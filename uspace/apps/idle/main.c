#include <libs/prelude.h>

result_t
main(void) {
    loop {
        /*
         * idle task. just make it available for interrupts,
         * as we only allow interrupt traps from user space.
         * if all other tasks are blocked, interrupts can still be handled.
         */
        /*
         * PM should register idle task as a protected task,
         * so that it will not be destroyed accidentally.
         */
    }
}