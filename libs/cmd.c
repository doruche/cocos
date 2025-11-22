#include <libs/prelude.h>
#include <libs/cmd.h>

void
cmd_skip_empty(char** cmd_str) {
    while (**cmd_str == ' ' || **cmd_str == '\t') {
        (*cmd_str)++;
    }
}

void
cmd_parse_inplace(char* input, cmdline_t* out) {
    char* ptr = input;
    cmd_skip_empty(&ptr);

    usize arg_idx = 0;
    while (*ptr != '\0' && arg_idx < NUM_CMD_ARGS_MAX) {
        char* start = ptr;
        while (*ptr != ' ' && *ptr != '\t' && *ptr != '\0') {
            ptr++;
        }
        usize len = ptr - start;
        if (len > 0) {
            out->argv[arg_idx] = start;
            if (*ptr != '\0') {
                *ptr = '\0'; /* null-terminate */
                ptr++;
            }
            arg_idx++;
        }
        cmd_skip_empty(&ptr);
    }
    out->argc = arg_idx;
    out->argv[arg_idx] = NULL;
}

/*
 * the returned cmdline_t* should be freed by the caller
 */

result_t
cmd_parse(const char* input, cmdline_t* out) {
    char* str = strdup(input);
    if (str == NULL) {
        return -ERR_NOMEM;
    }
    cmd_parse_inplace(str, out);
    return OK;
}

void
cmd_free(cmdline_t* cmdline) {
    /* 
     * note that the way we allocate memory for a command 
     * is to allocate a single block for the entire input string,
     * so we only need to free argv[0]
     */
    if (cmdline->argc == 0) {
        return;
    }
    free(cmdline->argv[0]);
}


