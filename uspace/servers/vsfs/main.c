#include "vsfs.h"
#include <libs/prelude.h>
#include <uspace/ipc.h>

result_t
main(usize argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: vsfs <dev> <name>\n");
        return -ERR_INVAL;
    }

    extern const char* dev;
    dev = argv[1];
    const char* fs_name = argv[2];

    todo()
}