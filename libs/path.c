#include <libs/path.h>
#include <libs/string.h>
#include <config.h>

/*
 * we do not check whether the paths are NULL pointers,
 * as it is easy to cause vague undefined behaviors.
 * to panic immediately can help catch bugs earlier.
 */

bool
path_is_absolute(const char *path) {
    return path[0] == '/';
}

bool
path_is_relative(const char *path) {
    return !path_is_absolute(path);
}

const char*
path_basename(const char *path) {
    usize n = strlen(path);
    
    /*
     * skip trailing slashes first, then
     * find the last slash
     */
    for (usize i = 0; i < 2; i++) {
        while (n > 0) {
            if (path[n - 1] != '/') {
                break;
            }
            n--;
        }
    }
    return path + n;
}


