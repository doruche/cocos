#include "libs/printf.h"
#include "uspace/task.h"
#include "libs/types.h"
#include "libs/macros.h"

u64 counter = 0;

isize
main(int argc, char* argv[]) {
    printf("hello from hello app!\n");

    loop {
        printf("hello counter: %ld\n", counter++);
        task_yield();
    }    

    return 0;
}