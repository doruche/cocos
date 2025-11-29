#include <libs/prelude.h>
#include <uspace/fd.h>

result_t
main(usize argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: cat <path> [bytes]\n");
        return -ERR_INVAL;
    }
    u64 fd;
    result_t ret = open(argv[1], O_RDONLY, &fd);
    if (is_err(fd)) {
        printf("cat: failed to open %s: %s\n", argv[1], strerr(fd));
        return fd;
    }
    u8 buf[512];
    usize bytes_read = 0;
    loop {
        ret = read(fd, buf, sizeof(buf), &bytes_read);
        if (is_err(ret)) {
            printf("cat: failed to read from %s: %s\n", argv[1], strerr(ret));
            return ret;
        }
        if (bytes_read == 0) {
            break;
        }
        printf("%s", (char*)buf);
    }
    return OK;
}