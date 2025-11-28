#include "uart.h"
#include <libs/prelude.h>
#include <uspace/syscall.h>
#include <uspace/ipc.h>

/*
 * currenly, this driver also serves as a simple tty driver.
 * you can see some tty-like behaviors, such as echoing input characters,
 * handling backspace, and appending newline on carriage return.
 * those are weird, as they almost only work on my local terminal.
 * i'll improve it later.
 */

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
    pr_trace("uart16550: MMIO mapped at vpn 0x%lx",
        msg.pm.map_resp.vpn);

    /* disable interrupts */
    *UART_COM(uart_base, COM_IER) = 0x00;
    /* disable fifo */
    *UART_COM(uart_base, COM_FCR) = 0x00;
    /* set baud rate */
    *UART_COM(uart_base, COM_LCR) = COM_LCR_DLAB;
    *UART_COM(uart_base, COM_DLL) = 0x03;
    *UART_COM(uart_base, COM_DLM) = 0x00;
    /* 1 start bit, 8 data bits, no parity, 1 stop bit */
    *UART_COM(uart_base, COM_LCR) = COM_LCR_WLEN8;
    /* turn off modem controls */
    *UART_COM(uart_base, COM_MCR) = 0x00;
    /* enable data ready interrupt */
    *UART_COM(uart_base, COM_IER) = COM_IER_RDI;
    pr_trace("uart16550: hardware initialized.");
}

static bool
uart_tx_busy(void) {
    return (*(volatile u8*)UART_COM(uart_base, COM_LSR) & COM_LSR_THRE) == 0;
}

static bool
uart_rx_ready(void) {
    return (*(volatile u8*)UART_COM(uart_base, COM_LSR) & COM_LSR_DR) != 0;
}

static result_t
uart_serial_write(const u8* buf, usize len) {
    for (usize i = 0; i < len; i++) {
        /* wait for THR empty */
        while (uart_tx_busy()) {
            /* wait */
        }
        *(volatile u8*)UART_COM(uart_base, COM_THR) = buf[i];
    }
    return OK;
}


static char rd_buf[SERIAL_BUF_MAX_LEN + 1] = {0};
static usize rd_buf_idx = 0;
static usize rd_req_len = 0;
static tid_t rd_req_tid = TID_INVALID;
static bool is_rd_waiting = false;

static result_t
uart_serial_read_register(tid_t tid, usize len) {
    if (is_rd_waiting) {
        return -ERR_DEV_BUSY;
    }
    if (len > SERIAL_BUF_MAX_LEN) {
        return -ERR_INVAL;
    }
    is_rd_waiting = true;
    rd_buf_idx = 0;
    rd_req_len = len;
    rd_req_tid = tid;
    pr_trace("uart16550: registered read request of len %ld from tid %ld",
        rd_req_len, rd_req_tid);
    return OK;
}

static result_t
uart_serial_read(void) {
    u8 byte = *(volatile u8*)UART_COM(uart_base, COM_RBR);
    if (is_rd_waiting) {
        if (byte == 0x08 || byte == 0x7f) {
            /* backspace */
            if (rd_buf_idx > 0) {
                rd_buf_idx--;
                /* echo backspace */
                const char bs_seq[] = {'\b', ' ', '\b'};
                uart_serial_write((const u8*)bs_seq, sizeof(bs_seq));
            }
        } else {
            if (byte == '\r') {
                /* convert carriage return to newline */
                byte = '\n';
            }
            rd_buf[rd_buf_idx++] = byte;  
            uart_serial_write(&byte, 1); /* echo back */
            bool rd_ready = 
                (rd_buf_idx == rd_req_len) ||
                (byte == '\n');
            if (rd_ready) {
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
                /* clear read request state */
                is_rd_waiting = false;
                rd_buf_idx = 0;
                rd_req_len = 0;
                rd_req_tid = TID_INVALID;
            }
        }
    }
    return OK;
}


result_t
main(void) {
    unwrap_err(sys_irq_listen(UART0_IRQ));
    unwrap_err(pns_publish("serial/uart16550"));

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
                    while (uart_rx_ready()) {
                        ret = uart_serial_read();
                        if (is_err(ret)) {
                            pr_warn("uart16550: serial_read failed: %s",
                                strerr(ret));
                        }
                    }
                    unwrap_err(sys_irq_ack(UART0_IRQ));
                }
                break; 
            }
            case MSG_SERIAL: {
                switch (msg.serial.type) {
                    case SERIAL_WRITE: {
                        ret = uart_serial_write(
                            msg.serial.write.buf,
                            msg.serial.write.len
                        );
                        pr_trace("uart16550: wrote %ld bytes from tid %ld",
                            msg.serial.write.len,
                            msg.src);
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
                        ret = uart_serial_read_register(
                            msg.src,
                            msg.serial.read.len
                        );
                        if (is_err(ret)) {
                            pr_warn("uart16550: serial_read_register failed: %s",
                            strerr(ret));
                            rpc_reply_result(msg.src, ret);        
                        }
                        /*
                         * this just register a read request 
                         * we'll response when data is available
                         */
                        break;
                        
                    }
                    default: {
                        pr_warn("uart16550: unknown serial msg type %ld from %ld",
                            msg.serial.type, msg.src);
                        break;
                    }
                }
                break;
            }
            default: {
                pr_warn("uart16550: received unknown msg type %ld from %ld",
                    msg.type, msg.src);
                break;
            }
        }
    }
}