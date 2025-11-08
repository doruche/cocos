#include "libs/prelude.h"
#include "uspace/syscall.h"
#include "uspace/servers/pm.h"

result_t
main(usize argc, char* argv[]) {
    printf("hello, cocos userland!\n");
    return 0;
}