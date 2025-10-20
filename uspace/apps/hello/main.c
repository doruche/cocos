#include "libs/printf.h"
#include "uspace/task.h"
#include "libs/types.h"

isize
main(int argc, char* argv[]) {
    printf("argc: %ld\n", (isize)argc);
    return 0;
}