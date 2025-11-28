#include "libs/prelude.h"
#include "uspace/task.h"

/* 
 * define in assembly to support arbitrary signatures:
 * 1. main(void)
 * 2. main(int argc, char** argv)
 */
extern result_t __main(usize argc, char* argv[]);

/* initialization functions */
extern void heap_init(void);
extern void fd_init(void);

void
crt0(usize argc, char* argv[]) {
    heap_init();
    fd_init();
    result_t ret = __main(argc, argv);
    console_flush();
    task_exit(ret);
}