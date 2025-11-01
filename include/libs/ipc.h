#pragma once
#include "libs/prelude.h"

typedef u64 notifications_t;            // async notification bitmask.
#define NOTIFICATION_ABORTED    (1L << 0) // message send aborted due to port closed
#define NOTIFICATION_IRQ       (1L << 1) // interrupt notification
#define NOTIFICATION_USER0    (1L << 16) // user defined notification bits start from bit 16
#define notification_is_user(n)  ((n) & 0xFFFF0000)

typedef u64 port_t;
#define PID_ANY     ((port_t)-1)
#define PID_INVALID ((port_t)0)
typedef u64 msg_mode_t;
#define MSG_MODE_NORM   ((msg_mode_t)(1L << 0))
#define MSG_MODE_NOTIFY ((msg_mode_t)(1L << 1))

typedef u64 msg_id_t;

typedef struct _msg_hdr_t {
    port_t      local;           // port on the local side
    port_t      remote;         // port on the remote side
    usize       size;           // total size of the message, including header
#define MSG_MAX_SIZE 256
    msg_mode_t  mode;           // message mode
    union {
        struct {
            msg_id_t id;            // custom message id. used by user
            u8  data[0];
        } msg;
        // notifications_t notifications;
    } body;
} msg_hdr_t;
typedef u64 port_flags_t;
#define PORT_SEND   (1L << 0)
#define PORT_RECV   (1L << 1)
// after 12 bits are special options for port transfer
#define PORT_TRANSFER_DISCARD   (1L << 12)
#define port_privs(flags) ((flags) & 0xFFF)
#define port_has_send(privs) (((privs) & PORT_SEND) != 0)
#define port_has_recv(privs) (((privs) & PORT_RECV) != 0)

typedef struct _p_stat_t {
    port_t  id;
    port_flags_t privs;
} p_stat_t; 
