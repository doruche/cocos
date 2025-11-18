/* 
 * Serial server protocol definitions
 */

#include <libs/prelude.h>

typedef enum _serial_msg_type_t {
    SERIAL_WRITE,
    SERIAL_WRITE_RESP,
    SERIAL_READ,
    SERIAL_READ_RESP,
} serial_msg_type_t;

#define SERIAL_BUF_MAX_LEN 128

typedef struct _serial_msg_t {
    serial_msg_type_t type;
    union {
        struct {
            u8 buf[SERIAL_BUF_MAX_LEN];
            usize len;
        } write;
        struct {
            usize written_len;
        } write_resp;
        struct {
            usize len;
        } read;
        struct {
            u8 buf[SERIAL_BUF_MAX_LEN];
            usize len;
        } read_resp;
    };
} serial_msg_t;


result_t serial_read(
    tid_t serial_server,
    u8* buf,
    usize len,
    usize* out_len
);
result_t serial_write(
    tid_t serial_server,
    const u8* buf,
    usize len
);
