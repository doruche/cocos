#pragma once
#include <libs/prelude.h>
#include <libs/list.h>

#define SERVICE_MAX_NUM 32

struct pn_entry {
    char name[SERVICE_NAME_MAX_LEN];
    tid_t server;
    list_elem_t node;
};

void    pns_init(void);
result_t pn_lookup(
    const char* name,
    tid_t* out
);
result_t pn_insert(
    const char* name,
    tid_t server
);
result_t pn_remove(const char* name);
void pn_cleanup(tid_t server);
