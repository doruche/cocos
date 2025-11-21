#include <libs/prelude.h>

result_t
main(usize argc, char* argv[]) {
    printf("arg: argc=%ld\n", argc);
    for (usize i = 0; i < argc; i++) {
        printf("arg[%ld]: %s\n", i, argv[i]);
    }
    return OK;
}