#include "uart.h"
#include <libs/prelude.h>
#include <uspace/syscall.h>
#include <uspace/ipc.h>
#include <uspace/task.h>

/*
 * currenly, this driver also serves as a simple tty driver.
 * you can see some tty-like behaviors, such as echoing input characters,
 * handling backspace, and appending newline on carriage return.
 * those are weird, as they almost only work on my local terminal.
 * i'll improve it later.
 */

#define UART_HANDLE 42

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
static bool is_eof_received = false;

static result_t
uart_serial_read_register(tid_t tid, usize len) {
    if (is_rd_waiting) {
        return -ERR_DEV_BUSY;
    }
    len = min(len, SERIAL_BUF_MAX_LEN);
    // if (len > SERIAL_BUF_MAX_LEN) {
    //     return -ERR_INVAL;
    // }
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
            msg_t resp = {0};
            if (byte == '\r') {
                /* convert carriage return to newline */
                byte = '\n';
            }
            if (byte == 4) { /* EOT */
                is_eof_received = true;
            } else {
                rd_buf[rd_buf_idx++] = byte;
                uart_serial_write(&byte, 1); /* echo back */
            }

            bool rd_ready = 
                (rd_buf_idx == rd_req_len) ||
                (byte == '\n') ||
                is_eof_received;

            if (rd_ready) {
                /* fulfill read request */
                resp.type = MSG_FS;
                resp.fs.type = FS_READ_RESP;
                resp.fs.read_resp.size = rd_buf_idx;
                memcpy(
                    resp.fs.read_resp.data,
                    rd_buf,
                    rd_buf_idx
                );
                rpc_reply(rd_req_tid, &resp);
                /* clear read request state */
                is_rd_waiting = false;
                rd_buf_idx = 0;
                rd_req_len = 0;
                rd_req_tid = TID_INVALID;
                is_eof_received = false;
            }
        }
    }
    return OK;
}


result_t
main(void) {
    unwrap_err(sys_irq_listen(UART0_IRQ));
    unwrap_err(pns_publish("uart16550"));
    unwrap_err(ns_mount("/dev/serial0", "uart16550"));

    uart_init();

    pr_info("uart16550 server started.");
    loop {
        msg_t msg;
        result_t ret = ipc_recv(IPC_OPEN, &msg);
        if (is_err(ret)) {
            pr_warn("uart16550: ipc_recv failed: %s",
                strerr(ret));
            continue;
        }
        msg_t resp = {0};
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
            case MSG_FS: {
                resp.type = MSG_FS;
                switch (msg.fs.type) {
                    case FS_GET: {
                        if (strcmp(msg.fs.get.path, "/") != 0) {
                            pr_warn("uart16550: fs_get invalid path %s",
                                msg.fs.get.path);
                            break;
                        }
                        resp.fs.type = FS_GET_RESP;
                        resp.fs.get_resp.handle = UART_HANDLE;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_READ: {
                        if (msg.fs.read.handle != UART_HANDLE) {
                            pr_warn("uart16550: fs_read invalid handle %ld",
                                msg.fs.read.handle);
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                        /* register read */
                        ret = uart_serial_read_register(
                            msg.src,
                            msg.fs.read.size
                        );
                        if (is_err(ret)) {
                            pr_warn("uart16550: serial_read_register failed: %s",
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                        }
                        /* reply will be sent when data is available */
                        break;
                    }
                    case FS_WRITE: {
                        if (msg.fs.write.handle != UART_HANDLE) {
                            pr_warn("uart16550: fs_write invalid handle %ld",
                                msg.fs.write.handle);
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                        ret = uart_serial_write(
                            msg.fs.write.data,
                            msg.fs.write.size
                        );
                        if (is_err(ret)) {
                            pr_warn("uart16550: serial_write failed: %s",
                                strerr(ret));
                            rpc_reply_result(msg.src, ret);
                            break;
                        }
                        resp.fs.type = FS_WRITE_RESP;
                        resp.fs.write_resp.size = msg.fs.write.size;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_STAT: {
                        if (strcmp(msg.fs.stat.path, "/") != 0) {
                            pr_warn("uart16550: fs_stat invalid path %s",
                                msg.fs.stat.path);
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                    }
                    case FS_FSTAT: {
                        if (msg.fs.type == FS_FSTAT &&
                            msg.fs.fstat.handle != UART_HANDLE) {
                            pr_warn("uart16550: fs_fstat invalid handle %ld",
                                msg.fs.fstat.handle);
                            rpc_reply_result(msg.src, -ERR_INVAL);
                            break;
                        }
                        resp.fs.type = FS_STAT_RESP;
                        stat_init(&resp.fs.stat_resp.stat);
                        resp.fs.stat_resp.stat.mode = S_IFCHR;
                        resp.fs.stat_resp.stat.size = 0;
                        resp.fs.stat_resp.stat.dev = task_gettid();
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case FS_UNLINK:
                    case FS_MKDIR:
                    case FS_RMDIR:
                    case FS_READDIR: {
                        rpc_reply_result(msg.src, -ERR_NOT_SUPPORTED);
                        break;
                    }
                    default: {
                        pr_warn("uart16550: unknown fs msg type %ld from %ld",
                            msg.fs.type, msg.src);
                        rpc_reply_result(msg.src, -ERR_UNKNOWN_REQ);
                        break;
                    }
                }
                break;
            }
            default: {
                pr_warn("uart16550: received unknown msg type %ld from %ld",
                    msg.type, msg.src);
                rpc_reply_result(msg.src, -ERR_UNKNOWN_REQ);    
                break;
            }
        }
    }

    pr_info("uart16550 server exiting.");
    return OK;
}