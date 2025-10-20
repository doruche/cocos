#include "libs/types.h"
#include "uspace/task.h"

// define in assembly thus allowing arbitrary signatures:
// 1. main(void)
// 2. main(int argc, char** argv)
extern isize __main(isize argc, char* argv[]);

void
crt0(void) {
    __main(0, NULL);
    exit();
}