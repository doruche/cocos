#include <libs/prelude.h>
#include <uspace/fd.h>

result_t
main(usize argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: touch <abs_path>\n");
        return -ERR_INVAL;
    }
    const char* path = argv[1];
    result_t ret = open(path, O_CREATE | S_IFREG, &(u64){0});
    if (is_err(ret)) {
        printf("touch: create '%s' failed: %s\n", path, strerr(ret));
    }
    return ret;
}