#include "libs/prelude.h"
#include "uspace/task.h"

// define in assembly to support arbitrary signatures:
// 1. main(void)
// 2. main(int argc, char** argv)
extern result_t __main(usize argc, char* argv[]);

void
crt0(usize argc, char* argv[]) {
    result_t ret = __main(argc, argv);
    printf_flush();
    task_exit(ret);
}