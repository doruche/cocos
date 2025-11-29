#include "console.h"
#include <uspace/ipc.h>
#include <uspace/task.h>
#include <uspace/fd.h>

static tid_t serial = TID_INVALID;

result_t
console_gets(char* buf) {
    loop {
        u64 fd;
        result_t ret = open("/dev/serial0", O_RDONLY, &fd);
        if (ret == -ERR_DEV_BUSY || ret == -ERR_NOT_FOUND) {
            task_yield();
            continue;
        } else if (is_err(ret)) {
            unwrap_err(close(fd));
            return ret;
        }
        unwrap_err(read(fd, buf, SERIAL_BUF_MAX_LEN, NULL));
        unwrap_err(close(fd));
        break;
    }
    if (buf[SERIAL_BUF_MAX_LEN - 1] != '\0' &&
        buf[SERIAL_BUF_MAX_LEN - 1] != '\n') {
        return -ERR_BUF_OVERFLOW;
    }
    return OK;
}
