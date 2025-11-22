#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/task.h>
#include <uspace/syscall.h>

void __noreturn
task_exit(result_t exit_code) {
    sys_task_exit(exit_code);
}

void
task_yield(void) {
    sys_task_yield();
}

tid_t
task_gettid(void) {
    static tid_t cached = 0;
    if (cached == 0) {
        cached = (tid_t)sys_task_gettid();
    }
    return cached;
}

result_t
proc_spawn(
    const char* path,
    const char* argv[],
    tid_t* out_pid
) {
    if (argv == NULL || argv[0] == NULL) {
        return -ERR_INVAL;
    }

    char cmdline_buf[SERIAL_BUF_MAX_LEN] = {0};
    isize written = 0;
    snprintf(cmdline_buf, SERIAL_BUF_MAX_LEN, "%s", argv[0]);
    for (usize i = 1; argv[i] != NULL; i++) {
        written += snprintf(
            cmdline_buf + written,
            SERIAL_BUF_MAX_LEN - written,
            " %s",
            argv[i]
        );
        if (written >= SERIAL_BUF_MAX_LEN) {
            return -ERR_NOMEM;
        }
    }

    msg_t msg = {0};
    msg.type = MSG_PM;
    msg.pm.type = PM_PROC_SPAWN;
    memcpy(msg.pm.proc_spawn.cmdline, cmdline_buf, SERIAL_BUF_MAX_LEN);
    
    char path_buf[PATH_MAX_LEN] = {0};
    strncpy(path_buf, path, PATH_MAX_LEN);
    memcpy(msg.pm.proc_spawn.path, path_buf, PATH_MAX_LEN);
    
    result_t ret = rpc_call(TID_PM, &msg);
    if (is_err(ret)) {
        return ret;
    }
    *out_pid = msg.pm.proc_spawn_resp.pid;
    return OK;
}
