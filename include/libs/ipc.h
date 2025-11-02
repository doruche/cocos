#pragma once
#include "libs/prelude.h"

typedef u64 notifications_t;            // async notification bitmask.
#define NOTIF_ABORTED   (1L << 0) // message send aborted due to port closed
#define NOTIF_IRQ       (1L << 1) // interrupt notification
#define NOTIF_USER0     (1L << 16) // user defined notification bits start from bit 16
#define NOTIF_MASK_ALL  ((notifications_t)(-1))
#define notif_is_user(n)  ((n) & 0xFFFF0000)
#define notif_intersects(n, mask) ((n) & (mask))

typedef u64 port_t;
#define PID_ANY     ((port_t)-1)
#define PID_INVALID ((port_t)0)

typedef u64 msg_id_t;

typedef struct _msg_hdr_t {
    port_t      local;           // port on the local side
    port_t      remote;         // port on the remote side
    usize       size;           // total size of the message, including header
#define MSG_MAX_SIZE 256
    msg_id_t id;            // custom message id. used by user
    u8 body[0];              // message body follows
} msg_hdr_t;
typedef u64 port_flags_t;
#define PORT_SEND       (1L << 0)
#define PORT_RECV       (1L << 1)
// after 12 bits are special options for port transfer
#define PORT_TRANSFER_DISCARD   (1L << 12)
#define port_privs(flags) ((flags) & 0xFFF)
#define port_has_send(privs) (((privs) & PORT_SEND) != 0)
#define port_has_recv(privs) (((privs) & PORT_RECV) != 0)

typedef struct _p_stat_t {
    port_t  id;
    port_flags_t privs;
} p_stat_t; 
