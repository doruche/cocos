#include <libs/prelude.h>
#include <uspace/servers/ns.h>

result_t
main(usize argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: mount <path> <fs_pid>\n");
        return -ERR_INVAL;
    }
    const char* path = argv[1];
    pid_t fs;
    result_t ret = str2isize(argv[2], (isize*)&fs);
    if (is_err(ret)) {
        printf("mount: invalid fs pid: %s\n", argv[2]);
        return ret;
    }

    ret = ns_mount(path, fs);
    if (is_err(ret)) {
        printf("mount: failed to mount %s to fs %d: %s\n", path, fs, strerr(ret));
        return ret;
    }

    return OK;
}
