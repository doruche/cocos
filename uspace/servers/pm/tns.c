#include "tns.h"
#include <libs/prelude.h>
#include <libs/list.h>
#include <uspace/servers/pm.h>
#include <uspace/syscall.h>
#include <uspace/ipc.h>

static struct tn_entry tn_table[SERVICE_MAX_NUM];
static list_t tn_list;

void
tns_init(void) {
    list_init(&tn_list);
    for (usize i = 0; i < SERVICE_MAX_NUM; i++) {
        tn_table[i] = (struct tn_entry){
            .name = {0},
            .server = TID_INVALID,
            .node = {0}
        };
    }
}

result_t
tn_lookup(
    const char* name,
    tid_t* out
) {
    list_foreach(iter, &tn_list) {
        struct tn_entry* entry = 
            list_entry(iter, struct tn_entry, node);
        if (strcmp(entry->name, name) == 0) {
            *out = entry->server;
            return OK;
        }
    }
    return -ERR_NOENT;
}

result_t
tn_insert(
    const char* name,
    tid_t server
) {
    list_foreach(iter, &tn_list) {
        struct tn_entry* entry = 
            list_entry(iter, struct tn_entry, node);
        if (strcmp(entry->name, name) == 0) {
            return -ERR_EXIST;
        }
    }

    for (usize i = 0; i < SERVICE_MAX_NUM; i++) {
        if (tn_table[i].server == TID_INVALID) {
            struct tn_entry* entry = &tn_table[i];
            strncpy(entry->name, name, SERVICE_NAME_MAX_LEN);
            entry->server = server;
            list_push_back(&tn_list, &entry->node);
            pr_trace("tn_insert: "
                "registered service '%s' with server %ld",
                entry->name,
                entry->server);
            return OK;
        }
    }

    return -ERR_NOSPC;
}

result_t
tn_remove(const char* name) {
    list_foreach_safe(iter, &tn_list, next) {
        struct tn_entry* entry = 
            list_entry(iter, struct tn_entry, node);
        if (strcmp(entry->name, name) == 0) {
            list_remove(&entry->node);
            entry->name[0] = '\0';
            entry->server = TID_INVALID;
            return OK;
        }
    }

    return -ERR_NOENT;
}
