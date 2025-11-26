#include <libs/prelude.h>
#include <uspace/ipc.h>

result_t
ns_mount(const char* path, pid_t fs) {
    tid_t ns_tid;
    unwrap_err(tns_resolve("ns", &ns_tid));
    msg_t msg;
    msg.type = MSG_NS;
    msg.ns.type = NS_MOUNT;
    msg.ns.mount.fs = fs;
    strncpy(msg.ns.mount.path, path, PATH_MAX_LEN);
    return rpc_call(ns_tid, &msg);
}

result_t
ns_umount(const char* path) {
    tid_t ns_tid;
    unwrap_err(tns_resolve("ns", &ns_tid));
    msg_t msg;
    msg.type = MSG_NS;
    msg.ns.type = NS_UMOUNT;
    strncpy(msg.ns.umount.path, path, PATH_MAX_LEN);
    return rpc_call(ns_tid, &msg);
}

result_t
ns_resolve(const char* path, pid_t* fs, char* rpath) {
    tid_t ns_tid;
    unwrap_err(tns_resolve("ns", &ns_tid));
    msg_t msg;
    msg.type = MSG_NS;
    msg.ns.type = NS_RESOLVE;
    strncpy(msg.ns.resolve.path, path, PATH_MAX_LEN);
    unwrap_err(rpc_call(ns_tid, &msg));
    if (msg.ns.type != NS_RESOLVE_RESP) {
        assert(msg.type == MSG_RESULT);
        return msg.result;
    }
    *fs = msg.ns.resolve_resp.fs;
    strncpy(rpath, msg.ns.resolve_resp.rpath, PATH_MAX_LEN);
    return OK;
}
