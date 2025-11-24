#pragma once
#include <libs/prelude.h>
#include <libs/list.h>

struct fs_file_t {
    struct filesystem_t* fss;
    handle_t handle;
    vfs_st_mode_t mode;
    char rpath[PATH_MAX_LEN];
    /*
     * reference count
     * when no process holds this file, we can close it in fs
     */
    usize rc;
    /*
     * if true, unlink the file in fs when rc drops to zero
     * this defers the actual unlink operation until all processes
     * close the file 
     */
    bool to_unlink;
    list_elem_t node;
};

result_t file_get(
    const char* path,
    bool create,
    bool mkdir,
    struct fs_file_t** out_file
);

result_t file_put(
    struct fs_file_t* file,
    bool unlink,
    bool rmdir
);

result_t file_read(
    struct fs_file_t* file,
    u8* buf,
    u64 size,
    usize offset,
    u64* out_size
);

result_t file_write(
    struct fs_file_t* file,
    const u8* buf,
    u64 size,
    usize offset,
    u64* out_size
);


