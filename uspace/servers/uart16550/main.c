#include "uart.h"
#include <libs/prelude.h>
#include <uspace/syscall.h>
#include <uspace/ipc.h>

static vaddr_t uart_base;

static void
uart_init(void) {
    /* request MMIO */
    msg_t msg = {0};
    msg.type = MSG_PM;
    msg.pm.type = PM_MAP;
    msg.pm.map.type = PM_MAP_MMIO;
    msg.pm.map.info.mmio.ppn = PA2PN(UART0_BASE);
    msg.pm.map.info.mmio.npages = 1;
    unwrap_err(rpc_call(TID_PM, &msg));
    uart_base = PN2PA(msg.pm.map_resp.vpn);
    pr_info("uart16550: MMIO mapped at vpn 0x%lx",
        msg.pm.map_resp.vpn);

    /* disable fifo */
    *(volatile u8*)UART_COM(uart_base, COM_FCR) = 0x00;
    /* set baud rate to 115200 */
    *(volatile u8*)UART_COM(uart_base, COM_LCR) = COM_LCR_DLAB;
    /* 1 start bit, 8 data bits, no parity, 1 stop bit */
    *(volatile u8*)UART_COM(uart_base, COM_LCR) = 
        COM_LCR_WLEN8 & !COM_LCR_DLAB;
    /* turn off modem controls */
    *(volatile u8*)UART_COM(uart_base, COM_MCR) = 0x00;
    /* enable data ready interrupt */
    *(volatile u8*)UART_COM(uart_base, COM_IER) = COM_IER_RDI;
    pr_info("uart16550: hardware initialized.");
}

static result_t
serial_write(const u8* buf, usize len) {
    for (usize i = 0; i < len; i++) {
        /* wait for THR empty */
        while ((*(volatile u8*)UART_COM(uart_base, COM_LSR) & COM_LSR_THRE) == 0) {
            /* wait */
        }
        *(volatile u8*)UART_COM(uart_base, COM_THR) = buf[i];
    }
    return OK;
}

static char rd_buf[SERIAL_BUF_MAX_LEN] = {0};
static usize rd_buf_idx = 0;
static usize rd_req_len = 0;
static tid_t rd_req_tid = TID_INVALID;
static bool is_rd_waiting = false;

result_t
main(void) {
    unwrap_err(sys_irq_listen(UART0_IRQ));
    unwrap_err(tns_publish("serial/uart16550"));

    uart_init();

    pr_info("serial/uart16550 server started.");

    loop {
        msg_t msg;
        result_t ret = ipc_recv(IPC_OPEN, &msg);
        if (is_err(ret)) {
            pr_warn("uart16550: ipc_recv failed: %s",
                strerr(ret));
            continue;
        }
        switch (msg.type) {
            case MSG_NOTIF: {
                if (msg.notifs & NOTIF_IRQ) {
                    pr_trace("uart16550: received IRQ notification");
                    while ((*(volatile u8*)UART_COM(uart_base, COM_LSR) & COM_LSR_DR) != 0) {
                        /* read data */
                        u8 byte = *(volatile u8*)UART_COM(uart_base, COM_RBR);
                        pr_trace("uart16550: received byte 0x%x ('%c')",
                            byte,
                            (byte >= 32 && byte <= 126) ? byte : '.');
                        if (is_rd_waiting) {
                            if (rd_buf_idx < rd_req_len) {
                                rd_buf[rd_buf_idx++] = byte;  
                                serial_write(&byte, 1); /* echo back */
                                if (rd_buf_idx == rd_req_len ||
                                byte == '\n' || byte == '\r') {
                                    /* fulfill read request */
                                    msg_t resp = {0};
                                    resp.type = MSG_SERIAL;
                                    resp.serial.type = SERIAL_READ_RESP;
                                    resp.serial.read_resp.len = rd_buf_idx;
                                    memcpy(
                                        resp.serial.read_resp.buf,
                                        rd_buf,
                                        rd_buf_idx
                                    );
                                    rpc_reply(rd_req_tid, &resp);
                                    is_rd_waiting = false;
                                    rd_buf_idx = 0;
                                    rd_req_len = 0;
                                    rd_req_tid = TID_INVALID;
                                }
                            }
                        }
                    }
                    unwrap_err(sys_irq_ack(UART0_IRQ));
                }
                break; 
            }
            case MSG_SERIAL: {
                switch (msg.serial.type) {
                    case SERIAL_WRITE: {
                        ret = serial_write(
                            msg.serial.write.buf,
                            msg.serial.write.len
                        );
                        if (is_err(ret)) {
                            pr_warn("uart16550: serial_write failed: %s",
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        msg_t resp = {0};
                        resp.type = MSG_SERIAL;
                        resp.serial.type = SERIAL_WRITE_RESP;
                        resp.serial.write_resp.written_len = msg.serial.write.len;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case SERIAL_READ: {
                        if (is_rd_waiting) {
                            pr_warn("uart16550: read request already pending from another task");
                            rpc_reply_result(msg.src, -ERR_DEV_BUSY);
                            break;
                        }
                        if (msg.serial.read.len > SERIAL_BUF_MAX_LEN) {
                            pr_warn("uart16550: read request length %ld exceeds buffer max len %ld",
                                msg.serial.read.len, SERIAL_BUF_MAX_LEN);
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                        is_rd_waiting = true;
                        rd_buf_idx = 0;
                        rd_req_len = msg.serial.read.len;
                        rd_req_tid = msg.src;
                        pr_info("uart16550: registered read request of len %ld from tid %ld",
                            rd_req_len, rd_req_tid);
                        break;
                        /*
                         * this just register a read request 
                         * we'll response when data is available
                         */
                    }
                    default: {
                        pr_warn("uart16550: unknown serial msg type %ld from %ld",
                            msg.serial.type, msg.src);
                        break;
                    }
                }
            }
            default: {
                pr_trace("uart16550: received unknown msg type %ld from %ld",
                    msg.type, msg.src);
                break;
            }
        }
    }
}