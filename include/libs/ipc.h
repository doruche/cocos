#pragma once
#include <libs/prelude.h>

/* server protocol headers */
#include <uspace/servers/pm.h>
#include <uspace/servers/echo.h>
#include <uspace/servers/serial.h>

/* IPC flags */
typedef u64 ipc_flags_t;
#define IPC_SEND     (1L << 0)
#define IPC_RECV     (1L << 1)
#define IPC_CALL     (IPC_SEND | IPC_RECV)
#define IPC_KERN     (1L << 2)
#define IPC_NONBLOCK (1L << 3)

/* IPC source */
#define IPC_OPEN    ((tid_t)-1) /* open receive */

/* IPC message struct */
#define MSG_SIZE (272)

typedef u64 msg_type_t;
/* kernel reserved */
#define MSG_NOTIF   0
#define MSG_EXCEPT  1
#define MSG_RESULT  2
/* user defined */
#define MSG_PM      3
#define MSG_ECHO    4
#define MSG_SERIAL  5

/* asynchronous notification */
typedef u64 notif_t;
/* kernel reserved */
#define NOTIF_IPC_ABORT (1L << 0)
#define NOTIF_TASK_EXIT (1L << 1)
#define NOTIF_IRQ       (1L << 2)
/* user defined */
#define NOTIF_USER0     (1L << 16)

typedef enum _except_type_t {
    EXCEPT_PAGEFAULT,
} except_type_t;
typedef struct _except_msg_t {
    except_type_t type;
    tid_t task;
    union {
        struct {
            uaddr_t fault_addr;
            bool is_write;  
        } pagefault;
    };
} except_msg_t;

/* synchronous message */
typedef struct _msg_t {
    tid_t   src;
    msg_type_t type;
    union {
        u8 raw[MSG_SIZE - 16];
        /* kernel reserved */
        notif_t notifs;
        except_msg_t except;
        result_t result;
        /* user defined */
        pm_msg_t pm;
        echo_msg_t echo;
        serial_msg_t serial;
    };
} msg_t;

static_assert(sizeof(msg_t) == MSG_SIZE);
