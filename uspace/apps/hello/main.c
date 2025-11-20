#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/syscall.h>

result_t
main(usize argc, char* argv[]) {
    printf("Hello, World!\n");

    return OK;
}