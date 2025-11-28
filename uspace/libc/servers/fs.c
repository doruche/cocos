#include <libs/prelude.h>
#include <libs/handle.h>
#include <uspace/ipc.h>

result_t
fs_get(tid_t fs, const char* path, handle_t* out) {
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_GET;
    strncpy(msg.fs.get.path, path, PATH_MAX_LEN);
    result_t ret = rpc_call(fs, &msg);
    if (is_err(ret)) {
        return ret;
    }
    *out = msg.fs.get_resp.handle;
    return OK;
}

result_t
fs_read(
    tid_t fs,
    handle_t handle,
    u8* buffer,
    u64 size,
    usize offset,
    usize* bytes_read
) {
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_READ;
    msg.fs.read.handle = handle;
    msg.fs.read.size = size;
    msg.fs.read.offset = offset;
    result_t ret = rpc_call(fs, &msg);
    if (is_err(ret)) {
        return ret;
    }
    usize to_copy = min(size, msg.fs.read_resp.size);
    strncpy((char*)buffer, (char*)msg.fs.read_resp.data, to_copy);
    *bytes_read = to_copy;
    return OK;
}

result_t
fs_write(
    tid_t fs,
    handle_t handle,
    const u8* buffer,
    u64 size,
    usize offset,
    usize* bytes_written
) {
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_WRITE;
    msg.fs.write.handle = handle;
    msg.fs.write.size = size;
    msg.fs.write.offset = offset;
    usize to_copy = min(size, FS_MAX_IO_SIZE);
    strncpy((char*)msg.fs.write.data, (const char*)buffer, to_copy);
    result_t ret = rpc_call(fs, &msg);
    if (is_err(ret)) {
        return ret;
    }
    *bytes_written = to_copy;
    return OK;
}

result_t
fs_unlink(tid_t fs, const char* path) {
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_UNLINK;
    strncpy(msg.fs.unlink.path, path, PATH_MAX_LEN);
    result_t ret = rpc_call(fs, &msg);
    return ret;
}

result_t
fs_mkdir(tid_t fs, const char* path) {
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_MKDIR;
    strncpy(msg.fs.mkdir.path, path, PATH_MAX_LEN);
    result_t ret = rpc_call(fs, &msg);
    return ret;
}

result_t
fs_readdir(
    tid_t fs,
    handle_t handle,
    usize offset,
    dirent_t* dirent,
    usize* next_offset
) {
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_READDIR;
    msg.fs.readdir.handle = handle;
    msg.fs.readdir.offset = offset;
    result_t ret = rpc_call(fs, &msg);
    if (is_err(ret)) {
        return ret;
    }
    *dirent = msg.fs.readdir_resp.dirent;
    *next_offset = msg.fs.readdir_resp.next_offset;
    return OK;
}

result_t
fs_rmdir(tid_t fs, const char* path) {
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_RMDIR;
    strncpy(msg.fs.rmdir.path, path, PATH_MAX_LEN);
    result_t ret = rpc_call(fs, &msg);
    return ret;
}

result_t
fs_stat(tid_t fs, const char* path, stat_t* out) {
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_STAT;
    strncpy(msg.fs.stat.path, path, PATH_MAX_LEN);
    result_t ret = rpc_call(fs, &msg);
    if (is_err(ret)) {
        return ret;
    }
    *out = msg.fs.stat_resp.stat;
    return OK;
}

result_t
fs_fstat(tid_t fs, handle_t handle, stat_t* out) {
    msg_t msg = {0};
    msg.type = MSG_FS;
    msg.fs.type = FS_FSTAT;
    msg.fs.fstat.handle = handle;
    result_t ret = rpc_call(fs, &msg);
    if (is_err(ret)) {
        return ret;
    }
    *out = msg.fs.stat_resp.stat;
    return OK;
}
