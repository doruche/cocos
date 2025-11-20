#include <libs/prelude.h>
#include <uspace/ipc.h>

result_t
serial_read(
    tid_t serial_server,
    u8* buf,
    usize len,
    usize* out_len
) {
    if (len > SERIAL_BUF_MAX_LEN) {
        return -ERR_INVAL;
    }

    msg_t msg = {0};
    msg.type = MSG_SERIAL;
    msg.serial.type = SERIAL_READ;
    msg.serial.read.len = len;

    result_t ret = rpc_call(serial_server, &msg);
    if (is_err(ret)) {
        return ret;
    }
    memcpy(buf, msg.serial.read_resp.buf, msg.serial.read_resp.len);
    *out_len = msg.serial.read_resp.len;

    return OK;
}

result_t
serial_write(
    tid_t serial_server,
    const u8* buf,
    usize len
) {
    if (len > SERIAL_BUF_MAX_LEN) {
        return -ERR_INVAL;
    }

    msg_t msg = {0};
    msg.type = MSG_SERIAL;
    msg.serial.type = SERIAL_WRITE;
    memcpy(msg.serial.write.buf, buf, len);
    msg.serial.write.len = len;

    result_t ret = rpc_call(serial_server, &msg);
    if (is_err(ret)) {
        return ret;
    }

    return OK;
}
