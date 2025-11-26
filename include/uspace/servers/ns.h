/* Name server protocol definitions */
#pragma once
#include <libs/prelude.h>

typedef enum {
    NS_MOUNT,
    NS_UMOUNT,
    NS_RESOLVE,
    NS_RESOLVE_RESP,
} ns_msg_type_t;

typedef struct {
    ns_msg_type_t type;
    union {
        struct {
            char path[PATH_MAX_LEN];
            pid_t fs;
        } mount;
        struct {
            char path[PATH_MAX_LEN];
        } umount;
        struct {
            char path[PATH_MAX_LEN];
        } resolve;
        struct {
            pid_t fs;
            char rpath[PATH_MAX_LEN];
        } resolve_resp;
    };
} ns_msg_t;

result_t ns_mount(const char* path, pid_t fs);
result_t ns_umount(const char* path);
result_t ns_resolve(const char* path, pid_t* out_fs, char* out_rpath);
