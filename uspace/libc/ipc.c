#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/syscall.h>
#include <uspace/task.h>

result_t
ipc_send(tid_t send_to, const msg_t *msg) {
    return sys_ipc(
        send_to,
        TID_INVALID,
        (msg_t*)msg,
        IPC_SEND
    );
}

result_t
ipc_send_nonblock(tid_t send_to, const msg_t *msg) {
    return sys_ipc(
        send_to,
        TID_INVALID,
        (msg_t*)msg,
        IPC_SEND | IPC_NONBLOCK
    );
}

result_t
ipc_recv(tid_t recv_from, msg_t *msg) {
    result_t ret = sys_ipc(
        TID_INVALID,
        recv_from,
        msg,
        IPC_RECV
    );
    if (is_err(ret)) {
        return ret;
    }
    if (msg->type == MSG_RESULT &&
    is_err(msg->result)) {
        return msg->result;
    }

    return OK;
}

result_t
ipc_notify(tid_t dst, notif_t notif) {
    return sys_notify(dst, notif);
}

result_t
rpc_call(tid_t remote, msg_t *msg) {
    result_t ret = sys_ipc(
        remote,
        remote,
        msg,
        IPC_CALL
    );
    if (is_err(ret)) {
        return ret;
    }
    if (msg->type == MSG_RESULT &&
    is_err(msg->result)) {
        return msg->result;
    }

    return OK;
}

result_t
rpc_reply(tid_t client, const msg_t *msg) {
    /*
     * we should not use synchronous send here,
     * as the server could not expect a client
     * to be blocked on receiving a reply.
     * non-blocking send may fail - if the client
     * is not ready to receive the reply yet.
     * the solution for this is to build a async
     * sending machanism on top of non-blocking send.
     * we'll do that later.
     */
    return ipc_send_nonblock(client, msg);
}

result_t
rpc_reply_result(tid_t client, result_t res) {
    msg_t msg = {0};
    msg.type = MSG_RESULT;
    msg.result = res;
    return ipc_send_nonblock(client, &msg);
}

result_t
pns_resolve(const char *name, tid_t *out) {
    msg_t msg = {0};
    msg.type = MSG_PM;
    msg.pm.type = PM_RESOLVE_NAME;
    strncpy(msg.pm.resolve_name.name, name, SERVICE_NAME_MAX_LEN);
 
    result_t ret = rpc_call(TID_PM, &msg);
    if (is_err(ret)) {
        return ret;
    }

    *out = msg.pm.resolve_name_resp.server_pid;
    return OK;
}

result_t
pns_publish(const char *name) {
    msg_t msg = {0};
    msg.type = MSG_PM;
    msg.pm.type = PM_PUBLISH;
    msg.pm.publish.server_pid = task_gettid();
    strncpy(msg.pm.publish.name, name, SERVICE_NAME_MAX_LEN);

    return rpc_call(TID_PM, &msg);
}

result_t
pns_unpublish(const char *name) {
    msg_t msg = {0};
    msg.type = MSG_PM;
    msg.pm.type = PM_UNPUBLISH;
    strncpy(msg.pm.unpublish.name, name, SERVICE_NAME_MAX_LEN);

    return rpc_call(TID_PM, &msg);
}
