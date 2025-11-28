/*
 * Process Manager server protocol definitions
 */

#pragma once

#include <libs/prelude.h>
#include <libs/cmd.h>

typedef enum _pm_msg_type_t {
    PM_PING,
    PM_PING_RESP,

#define SERVICE_NAME_MAX_LEN 32
    PM_RESOLVE_NAME,
    PM_RESOLVE_NAME_RESP,
    PM_PUBLISH,
    PM_UNPUBLISH,

    PM_MAP,
    PM_MAP_RESP,
    PM_UNMAP,

    PM_PROC_SPAWN,
    PM_PROC_SPAWN_RESP,
    PM_PROC_PROBE,
    PM_PROC_WATCH,
    PM_PROC_UNWATCH,
    PM_PROC_EXIT,
    PM_PROC_KILL,
    // PM_THREAD_XXX,

    PM_NS_MOUNT,
    PM_NS_UMOUNT,
    PM_NS_RESOLVE,
    PM_NS_RESOLVE_RESP,
} pm_msg_type_t;

typedef struct _pm_msg_t {
    pm_msg_type_t type;
    union {
        struct {
            usize val;
        } ping;
        struct {
            usize val;
        } ping_resp;
        struct {
            char name[SERVICE_NAME_MAX_LEN];
        } resolve_name;
        struct {
            tid_t server_pid;
        } resolve_name_resp;
        struct {
            char name[SERVICE_NAME_MAX_LEN];
            tid_t server_pid;
        } publish;
        struct {
            char name[SERVICE_NAME_MAX_LEN];
        } unpublish;
        struct {
            enum {
                PM_MAP_ANON,
                PM_MAP_MMIO,
            } type;
            union {
                struct {
                    usize npages;
                } anon;
                struct {
                    ppn_t ppn;
                    usize npages;
                } mmio;
            } info;
        } map;
        struct {
            vpn_t vpn;
            /*
             * this is for dma requirements.(drivers may need this. e.g. virtio)
             * we could actually make dma allocation a separate pm service,
             * but it seems overkill for now.
             */
            ppn_t ppn;
        } map_resp;
        struct {
            vpn_t vpn;
            usize npages;
        } unmap;
        struct {
            char path[PATH_MAX_LEN];
            char cmdline[SERIAL_BUF_MAX_LEN];
            bool inherit_ns;
        } proc_spawn;
        struct {
            tid_t pid;
        } proc_spawn_resp;
        struct {
            tid_t pid;
        } proc_probe;
        struct {
            tid_t pid;
        } proc_watch;
        struct {
            tid_t pid;
        } proc_unwatch;
        struct {
            tid_t pid;
            result_t xcode;
        } proc_exit; /* response of proc_watch */
        struct {
            tid_t pid;
        } proc_kill;

        struct {
            char path[PATH_MAX_LEN];
            /*
             * to mount a server, the server should publish itself first,
             * thus achieving great decoupling between pm and servers.
             * e.g.
             * 1. we publish a ramdisk server with name "ramdisk0"
             * 2. we mount it to /dev/tmpdisk0
             * 3. later we feel the size is not enough, we can shutdown the ramdisk0 server,
             *    start a new ramdisk1 server with larger size, 
             *    publish it with name "ramdisk0" again, and the mount point /dev/tmpdisk0
             *    will now refer to the new ramdisk1 server without unmounting/remounting.
             */
            char owner[SERVICE_NAME_MAX_LEN];
        } mount;
        struct {
            char path[PATH_MAX_LEN];
        } umount;
        struct {
            char path[PATH_MAX_LEN];
        } resolve;
        struct {
            tid_t owner;
            char rpath[PATH_MAX_LEN];
        } resolve_resp;
    };
} pm_msg_t;

/* process name system */
result_t pns_resolve(const char *name, tid_t *out);
result_t pns_publish(const char *name);
result_t pns_unpublish(const char *name);

result_t proc_spawn(
    const char* path, 
    const char* argv[], 
    bool inherit_ns,
    tid_t* out_pid
);
result_t proc_watch(tid_t pid);
result_t proc_unwatch(tid_t pid);
result_t proc_join(tid_t pid, result_t* xcode);
result_t proc_kill(tid_t pid);

result_t ns_mount(const char* path, const char* owner);
result_t ns_umount(const char* path);
result_t ns_resolve(
    const char* path,
    tid_t* out_owner,
    char* out_rpath
);
