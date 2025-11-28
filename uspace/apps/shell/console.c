#include "console.h"
#include <uspace/ipc.h>
#include <uspace/task.h>

static tid_t serial = TID_INVALID;

void
console_init(void) {
    while (is_err(pns_resolve("serial/uart16550", &serial))) {
        task_yield();        
    }
}

result_t
console_gets(char* buf) {
    loop {
        usize placeholder;
        result_t ret = serial_read(
            serial,
            (u8*)buf,
            SERIAL_BUF_MAX_LEN,
            &placeholder
        );
        if (ret == -ERR_DEV_BUSY) {
            task_yield();
            continue;
        }
        break;
    }
    if (buf[SERIAL_BUF_MAX_LEN - 1] != '\0' &&
        buf[SERIAL_BUF_MAX_LEN - 1] != '\n') {
        return -ERR_BUF_OVERFLOW;
    }
    return OK;
}
