#include <libs/prelude.h>
#include <libs/path.h>
#include <uspace/fd.h>

result_t
main(usize argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: ls <abs_path>\n");
        return -ERR_INVAL;
    }
    char* path = argv[1];
    u64 fd;
    result_t ret = open(path, O_RDONLY, &fd);
    if (is_err(ret)) {
        printf("ls: open '%s' failed: %s\n", path, strerr(ret));
        return ret;
    }
    stat_t st;
    ret = fstat(fd, &st);
    if (is_err(ret)) {
        printf("ls: fstat '%s' failed: %s\n", path, strerr(ret));
        return ret;
    }

    path_canonicalize(path, path);
    switch (st.mode & S_IFMT) {
        case S_IFREG: 
        case S_IFBLK:
        case S_IFCHR: {
            printf("%ld\t%s\t%ld\t%s\n",
                st.size,
                strfiletype(st.mode),
                st.ino,
                path
            );
            break;
        }
        case S_IFDIR: {
            struct dirent_t dirent;
            usize nxt_offset = 0;
            loop {
                ret = readdir(fd, &dirent, &nxt_offset);
                if (is_err(ret)) {
                    printf("ls: readdir '%s' failed: %s\n", path, strerr(ret));
                    return ret;
                }
                printf("%s\t%ld\t%s\n",
                    strfiletype(dirent.mode),
                    dirent.ino,
                    dirent.name
                );
                if (nxt_offset == 0) {
                    break;
                }
            }
            break;
        }
        default: {
            printf("ls: unknown file type for path '%s'\n", path);
            return -ERR_FMT;
        }
    }
    return OK;
} 