#include <libs/prelude.h>
#include <uspace/ipc.h>
#include <uspace/fd.h>

result_t
main(usize argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: stat <path>\n");
        return -ERR_INVAL;
    }
    const char* path = argv[1];
    stat_t st;
    result_t ret = stat(path, &st);
    if (is_err(ret)) {
        printf("stat: failed to stat %s: %s\n", path, strerr(ret));
        return ret;
    }
    printf("  File: %s\n", path);
    printf("  Size: %ld\tBlocks: %ld\tIO Block: %ld\t%s\n",
        st.size, st.blocks, st.blksize, strfiletype(st.mode));
    printf("Device: %ld\tInode: %ld\tLinks: %ld\n",
        st.dev, st.ino, st.nlink);
    
    return OK;
}