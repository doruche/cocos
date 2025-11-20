#include "cmd.h"
#include "console.h"

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

static void
skip_empty(char** str) {
    while (**str == ' ' || **str == '\t') {
        (*str)++;
    }
}

static result_t
cmd_parse(char* input, struct args_t* out_args) {
    char* ptr = input;
    skip_empty(&ptr);

    usize arg_idx = 0;
    while (*ptr != '\0' && arg_idx < NUM_ARGS_MAX) {
        char* start = ptr;
        while (*ptr != ' ' && *ptr != '\t' && *ptr != '\0') {
            ptr++;
        }
        usize len = ptr - start;
        if (len > 0) {
            out_args->argv[arg_idx] = start;
            if (*ptr != '\0') {
                *ptr = '\0'; /* null-terminate */
                ptr++;
            }
            arg_idx++;
        }
        skip_empty(&ptr);
    }
    out_args->argc = arg_idx;
    out_args->argv[arg_idx] = NULL;

    return OK;
}

result_t
main(void) {
    console_init();
    about_message();
    
    char buf[SERIAL_BUF_MAX_LEN] = {0};
    struct args_t args = {0};
    loop {
        prompt("");
        result_t ret = console_gets(buf);
        if (is_err(ret)) {
            printf("error reading input: %s\n", strerr(ret));
            goto done;
        }
        buf[strlen(buf) - 1] = '\0'; /* remove newline */
        
        char* p = buf;
        skip_empty(&p);
        if (*p == '\0') {
            continue; /* empty input */
        }

        ret = cmd_parse(buf, &args);
        if (is_err(ret)) {
            printf("error parsing command: %s\n", strerr(ret));
            goto done;
        }
        ret = cmd_run(&args);
        if (is_err(ret)) {
            printf("error executing command: %s\n", strerr(ret));
            goto done;
        }

    done:
        memset(buf, 0, SERIAL_BUF_MAX_LEN);
        memset(&args, 0, sizeof(args));
    }

    return OK;
}