#include "libs/prelude.h"
#include "uspace/task.h"

// define in assembly to support arbitrary signatures:
// 1. main(void)
// 2. main(int argc, char** argv)
extern result_t __main(isize argc, char* argv[]);

void
crt0(void) {
    result_t ret = __main(0, NULL);
    task_exit(ret);
}