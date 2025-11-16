#pragma once
#include <libs/prelude.h>

typedef u64 port_t;
#define PID_ANY     ((port_t)-2)
#define PID_INVALID ((port_t)-1)

/* kernel defined */
#define PID_PM      ((port_t)0)
/* pm defined */
#define PID_PNS     ((port_t)53)

#define MSG_SIZE 512
typedef struct _untyped_msg_t {
    u8 raw[MSG_SIZE];
} untyped_msg_t;

typedef struct _p_stat_t {
    port_t id;
    tid_t owner;
} p_stat_t;

/* asynchronous notification */
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
#define NOTIF_ABORTED   1L /* message send aborted due to port closed */
#define NOTIF_IRQ       2L /* interrupt notification */
#define NOTIF_TASK_EXIT 3L /* task exited notification */
#define NOTIF_USER0     42L /* user defined notification number start here */
