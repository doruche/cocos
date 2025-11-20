#include "cmd.h"
#include <uspace/ipc.h>

static result_t cmd_help(const struct args_t* args);

static result_t
cmd_echo(const struct args_t* args) {
    for (usize i = 1; i < args->argc; i++) {
        printf("%s ", args->argv[i]);
    }
    printf("\n");
    return OK;
}

static result_t
cmd_ping(const struct args_t* args) {
    if (args->argc != 2) {
        printf("usage: ping <number>\n");
        return -ERR_INVAL;
    }
    isize ping_val;
    result_t ret = str2isize(args->argv[1], &ping_val);
    if (is_err(ret)) {
        printf("ping: invalid number '%s'\n", args->argv[1]);
        return ret;
    }
    
    msg_t msg = {0};
    msg.type = MSG_PM;
    msg.pm.type = PM_PING;
    msg.pm.ping.val = (usize)ping_val;
    ret = rpc_call(TID_PM, &msg);
    if (is_err(ret)) {
        printf("ping: rpc_call to pm failed: %s\n", strerr(ret));
        return ret;
    }
    printf("ping response: %ld\n", (isize)msg.pm.ping_resp.val);

    return OK;
}

static const struct cmd_t cmds[] = {
    {
        .name = "help",
        .desc = "display this help message",
        .handler = cmd_help,
    },
    {
        .name = "echo",
        .desc = "echo the input arguments",
        .handler = cmd_echo,
    },
    {
        .name = "ping",
        .desc = "test command responsiveness of pm server",
        .handler = cmd_ping,
    }
};

static result_t
cmd_help(const struct args_t* args) {
    printf("available commands:\n");
    for (usize i = 0; i < array_size(cmds); i++) {
        printf("  %s:\t%s\n", cmds[i].name, cmds[i].desc);
    }
    return OK;
}

result_t
cmd_run(const struct args_t* args) {
    assert(args->argc > 0);
    const char* cmd_name = args->argv[0];
    for (usize i = 0; i < array_size(cmds); i++) {
        if (strcmp(cmd_name, cmds[i].name) == 0) {
            return cmds[i].handler(args);
        }
    }
    return -ERR_NOENT; /* no built-in command found */
}
