#include "builtin.h"
#include "console.h"
#include <libs/prelude.h>
#include <uspace/ipc.h>

#define COLOR_PROMPT COLOR_CYAN

static void
prompt(const char* msg) {
    printf(COLOR_PROMPT "sh> %s" COLOR_RESET, msg);
    printf_flush();
}

static void
about_message(void) {
    printf("cocos shell v0.1\n");
    printf("type 'help' to see available commands.\n");
}

result_t
main(void) {
    console_init();
    about_message();
    
    char buf[SERIAL_BUF_MAX_LEN] = {0};
    char buf2[SERIAL_BUF_MAX_LEN] = {0};
    cmdline_t args = {0};
    loop {
        prompt("");
        result_t ret = console_gets(buf);
        if (is_err(ret)) {
            printf("error reading input: %s\n", strerr(ret));
            goto done;
        }
        buf[strlen(buf) - 1] = '\0'; /* remove newline */
        memcpy(buf2, buf, SERIAL_BUF_MAX_LEN);

        char* p = buf;
        cmd_skip_empty(&p);
        if (*p == '\0') {
            continue; /* empty input */
        }

        cmd_parse_inplace(buf, &args);
        ret = builtin_run(&args);
        if (is_err(ret)) {
            msg_t m = {0};
            m.type = MSG_PM;
            m.pm.type = PM_SPAWN;
            memcpy(m.pm.spawn.cmdline, buf2, SERIAL_BUF_MAX_LEN);
            ret = rpc_call(TID_PM, &m);
            if (is_err(ret)) {
                printf("error executing command '%s': %s\n", buf, strerr(ret));
                goto done;
            } else {
                /* here we should wait. but now we just continue */
            }
        }

    done:
        memset(buf, 0, SERIAL_BUF_MAX_LEN);
        memset(buf2, 0, SERIAL_BUF_MAX_LEN);
        memset(&args, 0, sizeof(args));
    }

    return OK;
}