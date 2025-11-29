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
    while (n > 0) {
        if (path[n - 1] != '/') {
            break;
        }
        n--;
    }
    while (n > 0) {
        if (path[n - 1] == '/') {
            break;
        }
        n--;
    }

    return path + n;
}

const char*
path_skipcomp(
    const char* path,
    char* comp_buf
) {
    char* p = (char*)path;
    usize len = 0;

    while (*p == '/') {
        p++;
    }
    if (*p == '\0') {
        // no more components
        comp_buf[0] = '\0';
        return p;
    }
    while (*p != '/' && *p != '\0') {
        comp_buf[len++] = *p++;
    }
    comp_buf[len] = '\0';
    while (*p == '/') {
        p++;
    }
    return p;
}

/*
 * canonicalize an absolute path.
 * remove redundant slashes, and resolve "." and ".."
 * supports inplace operation (path and buf point to the same buffer).
 */
void
path_canonicalize(char* path, char* buf) {
    usize src = 0;
    usize dst = 0;

    buf[dst++] = '/';
    /* skip redundant slashes */
    while (path[src] == '/') {
        src++;
    }

    while (path[src] != '\0') {
        const char* scomp = path + src;
        usize len = 0;
        
        /* skip a component and slashes following it */
        while (path[src] != '/' && path[src] != '\0') {
            src++;
            len++;
        }
        while (path[src] == '/') {
            src++;
        }

        if (len == 0) {
            continue;
        }
        
        if (len == 1 && scomp[0] == '.') {
            continue;
        }
        
        if (len == 2 && scomp[0] == '.' && scomp[1] == '.') {
            /* backtrack */
            while (dst > 1) {
                dst--;
                if (buf[dst] == '/') {
                    break;
                }
            }
            if (dst == 0) {
                dst = 1;
            }
        } else {
            /* if not root directory, add a separator */
            if (dst > 1) {
                buf[dst++] = '/';
            }
            
            /*
             * the reason we don't use memcpy here is that
             * scomp may overlap with buf + dst when
             * path and buf point to the same buffer.
             */
            for (usize i = 0; i < len; i++) {
                buf[dst++] = scomp[i];
            }
        }
    }

    buf[dst] = '\0';
}

void
path_dupparent(const char *path, char *buf) {
    path_canonicalize((char*)path, buf);
    if (buf[0] == '/' && buf[1] == '\0') {
        // root dir has no parent
        return;
    }
    usize n = strlen(buf);
    /* skip last component */
    while (buf[n - 1] != '/' && n > 1) {
        n--;
    }
    
    if (n == 1) {
        // parent is root
        buf[0] = '/';
        buf[1] = '\0';
        return;
    }
    /* else, skip redundant slashes */
    buf[n - 1] = '\0';
}
