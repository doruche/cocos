#include "builtin.h"
#include "console.h"
#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/task.h>

#define COLOR_PROMPT COLOR_CYAN

static void
prompt(const char* msg) {
    printf(COLOR_PROMPT "sh> %s" COLOR_RESET, msg);
    console_flush();
}

static void
about_message(void) {
    printf("cocos shell v0.1\n");
    printf("type 'help' to see available commands.\n");
}

result_t
main(void) {
    about_message();
    
    char buf[SERIAL_BUF_MAX_LEN] = {0};
    cmdline_t args = {0};
    loop {
        prompt("");
        result_t ret = console_gets(buf);
        if (is_err(ret)) {
            printf("error reading input: %s\n", strerr(ret));
            goto done;
        }
        buf[strlen(buf) - 1] = '\0'; /* remove newline */

        bool background = false;
        ret = cmd_parse(buf, &args);
        if (is_err(ret)) {
            printf("error parsing command: %s\n", strerr(ret));
            goto done;
        }
        if (args.argc == 0) {
            /* empty command */
            goto done;
        }
        if (strcmp(args.argv[args.argc - 1], "&") == 0) {
            background = true;
            /* find '&' */
            usize amp_idx = strlen(buf) - 1;
            while (buf[amp_idx] != '&') {
                amp_idx--;
            }
            buf[amp_idx] = '\0';
        }

        bool exist = false;
        ret = builtin_run(&args, &exist);
        if (!exist) {
            msg_t m = {0};
            m.type = MSG_PM;
            m.pm.type = PM_PROC_SPAWN;

            /* refine later */
            m.pm.proc_spawn.inherit_ns = true;

            memcpy(m.pm.proc_spawn.cmdline, buf, SERIAL_BUF_MAX_LEN);
            memcpy(m.pm.proc_spawn.path, args.argv[0], PATH_MAX_LEN);
            ret = rpc_call(TID_PM, &m);
            if (is_err(ret)) {
                printf("error executing command '%s': %s\n", buf, strerr(ret));
                goto done;
            } else if (!background) {
                proc_join(m.pm.proc_spawn_resp.pid, NULL);
            }
        }

    done:
        memset(buf, 0, SERIAL_BUF_MAX_LEN);
        cmd_free(&args);
        memset(&args, 0, sizeof(cmdline_t));
    }

    return OK;
}