#include <libs/prelude.h>
#include <uspace/fd.h>

result_t
main(usize argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: write <abs_path> <data>\n");
        return -ERR_INVAL;
    }
    const char* path = argv[1];
    const char* data = argv[2];
    u64 fd;
    result_t ret = open(path, O_WRONLY | O_CREATE | S_IFREG, &fd);
    if (is_err(ret)) {
        printf("write: open '%s' failed: %s\n", path, strerr(ret));
        return ret;
    }
    usize bytes_written = 0;
    ret = write(fd, data, strlen(data), &bytes_written);
    if (is_err(ret)) {
        printf("write: write to '%s' failed: %s\n", path, strerr(ret));
        unwrap_err(close(fd));
        return ret;
    }
    printf("write: wrote %ld bytes to '%s'\n", bytes_written, path);
    unwrap_err(close(fd));
    return OK;
}