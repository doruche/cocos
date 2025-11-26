#include <libs/prelude.h>
#include <uspace/servers/ns.h>

result_t
main(usize argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: umount <path>\n");
        return -ERR_INVAL;
    }

    const char* path = argv[1];
    result_t ret = ns_umount(path);
    if (is_err(ret)) {
        printf("umount: failed to umount %s: %s\n", path, strerr(ret));
        return ret;
    }

    return OK;
}
