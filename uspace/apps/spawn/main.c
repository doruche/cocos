#include <libs/prelude.h>
#include <uspace/task.h>

/*
 * this program depends on the convention that
 * the first argument is the path to the executable to spawn,
 * followed by its arguments.
 * (and the zero-th argument is the program name itself)
 */
result_t
main(usize argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: spawn <path> [args...]\n");
        return -ERR_INVAL;
    }

    tid_t pid;
    result_t ret = proc_spawn(
        argv[1],
        (const char**)&argv[1],
        false,
        &pid
    );
    if (is_err(ret)) {
        printf("spawn: proc_spawn failed: %s\n", strerr(ret));
        return ret;
    } else {
        printf("spawn: spawned process '%s' with pid %ld\n",
            argv[1], pid);
    }

    return OK;
}