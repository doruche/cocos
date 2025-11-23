#include "file.h"
#include "filesystem.h"
#include <libs/prelude.h>
#include <uspace/ipc.h>

static list_head(open_files);

result_t
file_get(
    const char* path,
    bool create,
    struct fs_file_t** out_file
) {
    struct filesystem_t* fss = NULL;
    char rpath_buf[PATH_MAX_LEN] = {0};
    result_t ret = vfs_resolve(path, &fss, rpath_buf);
    if (is_err(ret)) {
        pr_warn("vfs: cannot resolve path %s\n", path);
        return ret;
    }
    
    list_foreach(iter, &open_files) {
        struct fs_file_t* file = list_entry(iter, struct fs_file_t, node);
        if (file->fss == fss && strcmp(file->rpath, rpath_buf) == 0) {
            file->rc += 1;
            *out_file = file;
            return OK;
        }
    }

    /* non-exist. try get it */
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_GET;
    msg.fs.get.create = create;
    strncpy(msg.fs.get.path, rpath_buf, PATH_MAX_LEN);
    ret = rpc_call(fss->fs, &msg);
    if (is_err(ret)) {
        pr_warn("vfs: cannot get file %s from fs %d\n", rpath_buf, fss->fs);
        return ret;
    }
    struct fs_file_t* fs_file = unwrap_null(
        malloc(sizeof(struct fs_file_t))
    );
    fs_file->fss = fss;
    fs_file->handle = msg.fs.get_resp.handle;
    strncpy(fs_file->rpath, rpath_buf, PATH_MAX_LEN);
    fs_file->rc = 1;
    fs_file->to_unlink = false;
    list_push_back(&open_files, &fs_file->node);
    *out_file = fs_file;
    
    return OK;
}

result_t
file_put(
    struct fs_file_t* file,
    bool unlink
) {
    assert(file->rc > 0);
    file->rc -= 1;
    file->to_unlink |= unlink;
    if (file->rc == 0) {
        msg_t msg = {0};
        msg.type = MSG_FS;
        msg.fs.type = FS_PUT;
        msg.fs.put.handle = file->handle;
        msg.fs.put.unlink = file->to_unlink;
        result_t ret = rpc_call(file->fss->fs, &msg);
        if (is_err(ret)) {
            pr_warn("vfs: cannot put file %s to fs %d\n",
                file->rpath, file->fss->fs
            );
            return ret;
        }
        list_remove(&file->node);
        free(file);
    }
    return OK;
}

result_t
file_read(
    struct fs_file_t* file,
    u8* buf,
    u64 size,
    usize offset,
    u64* out_size
) {
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_READ;
    msg.fs.read.handle = file->handle;
    msg.fs.read.offset = offset;
    msg.fs.read.size = size;
    result_t ret = rpc_call(file->fss->fs, &msg);
    if (is_err(ret)) {
        pr_warn("vfs: cannot read file %s from fs %d\n",
            file->rpath, file->fss->fs
        );
        return ret;
    }
    usize read_size = msg.fs.read_resp.size;
    memcpy(buf, msg.fs.read_resp.data, read_size);
    *out_size = read_size;
    return OK;
}

result_t
file_write(
    struct fs_file_t* file,
    const u8* buf,
    u64 size,
    usize offset,
    u64* out_size
) {
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_WRITE;
    msg.fs.write.handle = file->handle;
    msg.fs.write.size = size;
    msg.fs.write.offset = offset;
    usize write_size = min(size, 256);
    memcpy(msg.fs.write.data, buf, write_size);
    result_t ret = rpc_call(file->fss->fs, &msg);
    if (is_err(ret)) {
        pr_warn("vfs: cannot write file %s to fs %d\n",
            file->rpath, file->fss->fs
        );
        return ret;
    }
    *out_size = msg.fs.write_resp.size;
    return OK;
}

