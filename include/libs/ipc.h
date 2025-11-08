#pragma once
#include <libs/prelude.h>

typedef u64 port_t;
#define PID_ANY     ((port_t)-2)
#define PID_INVALID ((port_t)-1)
#define PID_PM      ((port_t)0)
typedef u64 port_flags_t;
#define PORT_SEND       (1L << 0)
#define PORT_RECV       (1L << 1)
// after 12 bits are special options for port transfer
#define PORT_TRANSFER_DISCARD   (1L << 12)
#define port_privs(flags) ((flags) & 0xFFF)
#define port_has_send(privs) (((privs) & PORT_SEND) != 0)
#define port_has_recv(privs) (((privs) & PORT_RECV) != 0)


#define MSG_MAX_SIZE 256
typedef u64 msg_id_t;
typedef struct _msg_hdr_t {
    union {
        port_t  local; // for senders, local port
        port_t  remote; // for receivers, remote port
    };
    struct {
        port_t  port; // auxiliary port to transfer
        port_flags_t flags; // transfer flags
    } aux_xfer;
    msg_id_t id;            // custom message id. used by user
    u8 body[0];              // message body follows
} msg_hdr_t;

typedef struct _p_stat_t {
    port_t  id;
    port_flags_t privs;
} p_stat_t; 

typedef struct _notif_t {
    union {
        /* port that was closed causing the aborted notification */
        port_t port_aborted;
        /* IRQ number */
        irq_t irqno;
        /* exited task */
        struct {
            tid_t tid;
            result_t exit_code;
        } task_exited;
        /* user defined */
        u8 raw[16];
    } payload;
    u64 type;
} notif_t;
#define NOTIF_ABORTED   1L // message send aborted due to port closed
#define NOTIF_IRQ       2L // interrupt notification
#define NOTIF_TASK_EXIT 3L // task exited notification
#define NOTIF_USER0     16L // user defined notification bits start from bit 16
#define NOTIF_MASK_ALL  ((u64)(-1))

