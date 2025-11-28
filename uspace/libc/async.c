#include <libs/prelude.h>
#include <libs/list.h>
#include <uspace/ipc.h>

/*
 * currently only support one async message source
 * we may extend it to multiple sources later
 * (e.g. add a register_async_source function, and
 * then poll each one until OK?) 
 */

static list_head(pending_msgs);

result_t
async_send(tid_t send_to, const msg_t *msg) {
    async_msg_t *amsg = malloc(sizeof(async_msg_t));
    if (amsg == NULL) {
        return -ERR_NOMEM;
    }
    
    result_t ret = ipc_notify(send_to, NOTIF_ASYNC_PENDING);
    if (is_err(ret)) {
        free(amsg);
        return ret;
    }
    
    amsg->send_to = send_to;
    memcpy(&amsg->msg, msg, sizeof(msg_t));
    list_push_back(&pending_msgs, &amsg->node);
    return OK;
}

result_t
async_recv(tid_t recv_from, msg_t *msg) {
    msg->type = MSG_ASYNC_PULL;
    return rpc_call(recv_from, msg);
}

/*
 * when we receive MSG_ASYNC_PULL,
 * call this function to flush pending messages
 * to the receiver.
 */
result_t
async_flush(tid_t send_to) {
    result_t ret = OK;
    bool already_sent = false;
    list_foreach_safe(iter, &pending_msgs, next) {
        async_msg_t* amsg = list_entry(iter, async_msg_t, node);
        if (amsg->send_to != send_to) {
            continue;
        }
        if (already_sent) {
            ret = ipc_notify(send_to, NOTIF_ASYNC_PENDING);
            break;
        }
        ret = ipc_send_nonblock(amsg->send_to, &amsg->msg);
        if (is_err(ret)) {
            break;
        }
        list_remove(&amsg->node);
        free(amsg);
        already_sent = true;
        pr_info("async_flush: sent async message to %ld", send_to);
    }

    if (is_err(ret)) {
        pr_warn("async_flush: failed to send async message: %s", strerr(ret));
    }
    if (!already_sent) {
        rpc_reply_result(send_to, -ERR_NOT_FOUND);
    }
    return ret;
}
