#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/syscall.h>

result_t
main(usize argc, char* argv[]) {
    tid_t serial;
    while (is_err(tns_resolve("serial/uart16550", &serial))) {
        sys_task_yield();
    }
    
    char buf[SERIAL_BUF_MAX_LEN] = {0};
    usize read_len;
    unwrap_err(serial_read(
        serial,
        (u8*)buf,
        32,
        &read_len
    ));
    printf("hello: read %ld bytes from serial: '%s'",
        read_len,
        buf
    );
    printf("hello: writing back to serial...");
    unwrap_err(serial_write(
        serial,
        (u8*)buf,
        read_len
    ));

    printf("hello: serial test completed.");

    return OK;
}