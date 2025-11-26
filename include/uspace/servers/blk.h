/* block device driver protocol definitions */
#include <libs/prelude.h>

typedef enum {
    BLK_READ,
    BLK_READ_RESP,
    BLK_WRITE,
    BLK_GET_SIZE,
    BLK_GET_SIZE_RESP,
} blk_msg_type_t;

typedef struct {
    blk_msg_type_t type;
    union {
        struct {
            u64 blkno;
        } read;
        struct {
            u8 data[1024];
        } read_resp;
        struct {
            u64 blkno;
            u8 data[1024];
        } write;
        struct {
            ;
        } get_size;
        struct {
            usize nblock;
            usize block_size;
        } get_size_resp;
    };
} blk_msg_t;

result_t blk_get_size(tid_t blk_server, usize *out_nblock, usize *out_block_size);
result_t blk_read(tid_t blk_server, u64 blkno, u8 *out_buf);
result_t blk_write(tid_t blk_server, u64 blkno, const u8 *buf);
