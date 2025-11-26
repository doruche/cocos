#include "builtin.h"
#include <uspace/ipc.h>
#include <uspace/task.h>
#include <uspace/syscall.h>

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

static result_t
builtin_blk(const cmdline_t* cmdline) {
    if (cmdline->argc == 1 || strcmp(cmdline->argv[1], "help") == 0) {
        printf("blk command usage:\n");
        printf("  blk help                : display this help message\n");
        printf("  blk read <dev> <blkno>       : read a block from the block device\n");
        printf("  blk write <dev> <blkno> <data>: write a block to the block device\n");
        printf("  blk info <dev>            : get block device info\n");
        return OK;
    }
    const char* subcmd = cmdline->argv[1];
    const char* dev = cmdline->argv[2];
    if (dev == NULL) {
        printf("blk: device name is required\n");
        return -ERR_INVAL;
    }
    tid_t blk_server = TID_INVALID;
    usize blkno;
    result_t ret = OK;
    ret = tns_resolve(dev, &blk_server);
    if (is_err(ret)) {
        printf("blk: failed to resolve block device '%s': %s\n", dev, strerr(ret));
        return ret;
    }
    if (strcmp(subcmd, "read") == 0) {
        if (cmdline->argc != 3 + 1) {
            printf("usage: blk read <dev> <blkno>\n");
            return -ERR_INVAL;
        }
        ret = str2isize(cmdline->argv[3], (isize*)&blkno);
        if (is_err(ret)) {
            printf("blk: invalid block number '%s'\n", cmdline->argv[3]);
            return ret;
        }
        u8 buf[1024] = {0};
        ret = blk_read(blk_server, (u64)blkno, buf);
        if (is_err(ret)) {
            printf("blk: read failed: %s\n", strerr(ret));
            return ret;
        }
        printf("blk: read block %ld: \n", blkno);
        /* print first 256 bytes */
        for (usize i = 0; i < 16; i++) {
            for (usize j = 0; j < 16; j++) {
                printf("0x%x ", buf[i * 16 + j]);
            }
            printf("\n");
        }
        printf("...\n");
    } else if (strcmp(subcmd, "write") == 0) {
        if (cmdline->argc != 4 + 1) {
            printf("usage: blk write <dev> <blkno> <data>\n");
            return -ERR_INVAL;
        }
        ret = str2isize(cmdline->argv[3], (isize*)&blkno);
        if (is_err(ret)) {
            printf("blk: invalid block number '%s'\n", cmdline->argv[3]);
            return ret;
        }
        const char* data_str = cmdline->argv[4];
        u8 buf[1024] = {0};
        usize data_len = strlen(data_str);
        if (data_len > sizeof(buf)) {
            data_len = sizeof(buf);
        }
        memcpy(buf, data_str, data_len);
        ret = blk_write(blk_server, (u64)blkno, buf);
        if (is_err(ret)) {
            printf("blk: write failed: %s\n", strerr(ret));
            return ret;
        }
        printf("blk: wrote block %ld\n", blkno);
    } else if (strcmp(subcmd, "info") == 0) {
        if (cmdline->argc != 2 + 1) {
            printf("usage: blk info <dev>\n");
            return -ERR_INVAL;
        }
        usize nblock, block_size;
        ret = blk_get_size(blk_server, &nblock, &block_size);
        if (is_err(ret)) {
            printf("blk: get info failed: %s\n", strerr(ret));
            return ret;
        }
        printf("blk: device info for '%s':\n", dev);
        printf("  block size: %ld bytes\n", block_size);
        printf("  total blocks: %ld\n", nblock);
    } else {
        printf("blk: unknown subcommand '%s'\n", subcmd);
        return -ERR_INVAL;
    }
    return OK;
}

static result_t
builtin_kdb(const cmdline_t* cmdline) {
    if (cmdline->argc != 2) {
        printf("usage: kdb <command>\n");
        return -ERR_INVAL;
    }
    const char* kdb_cmd = cmdline->argv[1];
    result_t ret = sys_kdb(kdb_cmd);
    if (is_err(ret)) {
        return ret;
    }
    return OK;
}

static result_t
builtin_kill(const cmdline_t* cmdline) {
    if (cmdline->argc != 2) {
        printf("usage: kill <pid>\n");
        return -ERR_INVAL;
    }
    pid_t pid;
    result_t ret = str2isize(cmdline->argv[1], (isize*)&pid);
    if (is_err(ret)) {
        printf("kill: invalid pid '%s'\n", cmdline->argv[1]);
        return ret;
    }
    ret = proc_kill(pid);
    if (is_err(ret)) {
        printf("kill: failed to kill pid %ld: %s\n", pid, strerr(ret));
        return ret;
    }
    printf("kill: killed pid %ld\n", pid);
    return OK;
}

static const struct builtin_cmd cmds[] = {
    { .name = "help", .desc = "display this help message", .handler = builtin_help, },
    { .name = "echo", .desc = "echo the input arguments", .handler = builtin_echo, },
    { .name = "ping", .desc = "test responsiveness of pm server", .handler = builtin_ping, },
    { .name = "rand", .desc = "generate a random number", .handler = builtin_random, },
    { .name = "blk", .desc = "block device operations", .handler = builtin_blk, },
    { .name = "kdb", .desc = "kernel debugger", .handler = builtin_kdb, },
    { .name = "kill", .desc = "kill a process by pid", .handler = builtin_kill, },
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
