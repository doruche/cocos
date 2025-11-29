#include <libs/prelude.h>
#include <uspace/fd.h>

result_t
main(usize argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: mkdir <abs_path>\n");
        return -ERR_INVAL;
    }
    const char* path = argv[1];
    u64 fd;
    result_t ret = open(path, O_CREATE | S_IFDIR, &fd);
    if (is_err(ret)) {
        printf("mkdir: open '%s' failed: %s\n", path, strerr(ret));
        return ret;
    }
    unwrap_err(close(fd));
    return OK;
}