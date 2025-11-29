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

    result_t ret = vsfs_mount();
    if (is_err(ret)) {
        printf("vsfs: failed to mount filesystem on %s: %s\n",
            dev,
            strerr(ret));
        return ret;
    }
    unwrap_err(pns_publish(fs_name));
    

    loop {

    }

    pr_info("vsfs: server exiting.");
    return OK;
}