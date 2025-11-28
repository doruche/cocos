#include <libs/prelude.h>
#include <uspace/servers/pm.h>

result_t
main(usize argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: mount <path> <owner>\n");
        return -ERR_INVAL;
    }
    const char* path = argv[1];
    const char* owner = argv[2];
    

    result_t ret = ns_mount(path, owner);
    if (is_err(ret)) {
        printf("mount: failed to mount %s to service owner %s: %s\n",
            path, owner, strerr(ret));
        return ret;
    }

    return OK;
}
