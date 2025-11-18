#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/syscall.h>

result_t
main(usize argc, char* argv[]) {
    // printf("hello, cocos userland!\n");
    
    tid_t serial;
    while (is_err(tns_resolve("serial/uart16550", &serial))) {
        sys_task_yield();
    }
    pr_info("hello: resolved 'serial/uart16550' server at tid %ld", serial);

    msg_t msg = {0};
    msg.type = MSG_SERIAL;
    msg.serial.type = SERIAL_READ;
    msg.serial.read.len = 64;
    result_t ret = rpc_call(serial, &msg);
    if (is_err(ret)) {
        pr_warn("hello: rpc_call to serial server failed: %s",
            strerr(ret));
    }
    msg.serial.read_resp.buf[msg.serial.read_resp.len - 1] = '\0';
    pr_info("hello: received serial read response: '%s'",
        msg.serial.read_resp.buf);
    
    msg.serial.type = SERIAL_WRITE;
    const char* hello_str = "Hello, cocos serial server!\n";
    memcpy(msg.serial.write.buf, hello_str, strlen(hello_str) + 1);
    msg.serial.write.len = strlen(hello_str) + 1;
    unwrap_err(rpc_call(serial, &msg));

    return 0;
}