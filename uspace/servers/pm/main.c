#include "libs/printf.h"
#include "uspace/task.h"
#include "libs/panic.h"

isize
main(void) {
    printf("Hello, World!\n");

    __panic("test panic\n");    

    return 0;
}