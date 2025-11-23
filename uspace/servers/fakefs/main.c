#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/task.h>

result_t
main(usize argc, char* argv[]) {
    if (argc != 2) {
        printf("fakefs: usage: fakefs <mount_point>\n");
        return -ERR_INVAL;
    }
    const char* mountp = argv[1];

    tid_t vfs;
    while (is_err(tns_resolve("vfs", &vfs))) {
        task_yield();
    }

    /* fakefs mount */
    msg_t msg = {0};
    msg.type = MSG_VFS;
    msg.vfs.type = VFS_MOUNT;
    strncpy(msg.vfs.mount.path, mountp, PATH_MAX_LEN);
    unwrap_err(rpc_call(vfs, &msg));

    pr_info("fakefs server mounted at '%s'", mountp);

    loop {}

    /* test umount */
    return OK;
}
