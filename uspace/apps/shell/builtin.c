#include "builtin.h"
#include <uspace/ipc.h>
#include <uspace/task.h>

static result_t builtin_help(const cmdline_t* cmdline);

static result_t
builtin_echo(const cmdline_t* cmdline) {
    for (usize i = 1; i < cmdline->argc; i++) {
        printf("%s ", cmdline->argv[i]);
    }
    printf("\n");
    return OK;
}

static result_t
builtin_ping(const cmdline_t* cmdline) {
    if (cmdline->argc != 2) {
        printf("usage: ping <number>\n");
        return -ERR_INVAL;
    }
    isize ping_val;
    result_t ret = str2isize(cmdline->argv[1], &ping_val);
    if (is_err(ret)) {
        printf("ping: invalid number '%s'\n", cmdline->argv[1]);
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

static result_t
builtin_random(const cmdline_t* cmdline) {
    if (cmdline->argc > 2) {
        printf("usage: random [seed]\n");
        return -ERR_INVAL;
    }
    result_t ret = OK;
    tid_t random_server = TID_INVALID;
    ret = tns_resolve("random", &random_server);
    if (is_err(ret)) {
        printf("random: failed to resolve random server: %s\n", strerr(ret));
        return ret;
    }

    msg_t msg = {0};
    msg.type = MSG_RANDOM;
    if (cmdline->argc == 2) {
        isize seed;
        ret = str2isize(cmdline->argv[1], &seed);
        if (is_err(ret)) {
            printf("random: seed is not a valid number: %s\n", strerr(ret));
            return ret;
        }
        msg.random.type = RANDOM_GEN_WITH_SEED;
        msg.random.gen_with_seed.seed = (usize)seed;
        ret = rpc_call(random_server, &msg);
        if (is_err(ret)) {
            printf("random: rpc_call to random server failed: %s\n", strerr(ret));
            return ret;
        }
        printf("random: generated random number %ld\n", msg.random.gen_resp.val);
    } else {
        msg.random.type = RANDOM_GEN;
        ret = rpc_call(random_server, &msg);
        if (is_err(ret)) {
            printf("random: rpc_call to random server failed: %s\n", strerr(ret));
            return ret;
        }
        printf("random: generated random number %ld\n", msg.random.gen_resp.val);
    }
    return OK;
}

static result_t __noreturn
builtin_exit(const cmdline_t* cmdline) {
    printf("exiting shell...\n");
    task_exit(OK);
}

static const struct builtin_cmd cmds[] = {
    { .name = "help", .desc = "display this help message", .handler = builtin_help, },
    { .name = "echo", .desc = "echo the input arguments", .handler = builtin_echo, },
    { .name = "ping", .desc = "test responsiveness of pm server", .handler = builtin_ping, },
    { .name = "random", .desc = "generate a random number", .handler = builtin_random, },
    { .name = "exit", .desc = "exit the shell", .handler = builtin_exit, }
};

static result_t
builtin_help(const cmdline_t* cmdline) {
    printf("available commands:\n");
    for (usize i = 0; i < array_size(cmds); i++) {
        printf("  %s:\t%s\n", cmds[i].name, cmds[i].desc);
    }
    return OK;
}

result_t
builtin_run(const cmdline_t* cmdline, bool* exist) {
    assert(cmdline->argc > 0);
    const char* cmd_name = cmdline->argv[0];
    for (usize i = 0; i < array_size(cmds); i++) {
        if (strcmp(cmd_name, cmds[i].name) == 0) {
            *exist = true;
            return cmds[i].handler(cmdline);
        }
    }
    *exist = false;
    return -ERR_NOENT; /* no built-in command found */
}
