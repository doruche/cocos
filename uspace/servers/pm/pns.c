#include "pns.h"
#include <libs/prelude.h>
#include <libs/list.h>
#include <uspace/syscall.h>
#include <uspace/ipc.h>

static struct pn_entry pn_table[SERVICE_MAX_NUM];
static list_t pn_list;

void
pns_init(void) {
    list_init(&pn_list);
    for (usize i = 0; i < SERVICE_MAX_NUM; i++) {
        pn_table[i] = (struct pn_entry){
            .name = {0},
            .server = TID_INVALID,
            .node = {0}
        };
    }
}

result_t
pn_lookup(
    const char* name,
    tid_t* out
) {
    list_foreach(iter, &pn_list) {
        struct pn_entry* entry = 
            list_entry(iter, struct pn_entry, node);
        if (strcmp(entry->name, name) == 0) {
            *out = entry->server;
            return OK;
        }
    }
    return -ERR_NOT_FOUND;
}

result_t
pn_insert(
    const char* name,
    tid_t server
) {
    list_foreach(iter, &pn_list) {
        struct pn_entry* entry = 
            list_entry(iter, struct pn_entry, node);
        if (strcmp(entry->name, name) == 0) {
            return -ERR_EXIST;
        }
    }

    for (usize i = 0; i < SERVICE_MAX_NUM; i++) {
        if (pn_table[i].server == TID_INVALID) {
            struct pn_entry* entry = &pn_table[i];
            strncpy(entry->name, name, SERVICE_NAME_MAX_LEN);
            entry->server = server;
            list_push_back(&pn_list, &entry->node);
            pr_trace("pn_insert: "
                "registered service '%s' with server %ld",
                entry->name,
                entry->server);
            return OK;
        }
    }

    return -ERR_NOSPC;
}

result_t
pn_remove(const char* name) {
    list_foreach_safe(iter, &pn_list, next) {
        struct pn_entry* entry = 
            list_entry(iter, struct pn_entry, node);
        if (strcmp(entry->name, name) == 0) {
            list_remove(&entry->node);
            entry->name[0] = '\0';
            entry->server = TID_INVALID;
            return OK;
        }
    }

    return -ERR_NOT_FOUND;
}

void
pn_cleanup(tid_t server) {
    list_foreach_safe(iter, &pn_list, next) {
        struct pn_entry* entry = 
            list_entry(iter, struct pn_entry, node);
        if (entry->server == server) {
            pr_trace("pn_cleanup: removing service '%s' with server %ld",
                entry->name,
                entry->server);
            list_remove(&entry->node);
            entry->name[0] = '\0';
            entry->server = TID_INVALID;
        }
    }
}
