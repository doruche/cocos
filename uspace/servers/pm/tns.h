#pragma once
#include <libs/prelude.h>
#include <libs/list.h>

#define SERVICE_MAX_NUM 32

struct tn_entry {
    char name[SERVICE_NAME_MAX_LEN];
    tid_t server;
    list_elem_t node;
};

void    tns_init(void);
result_t tn_lookup(
    const char* name,
    tid_t* out
);
result_t tn_insert(
    const char* name,
    tid_t server
);
result_t tn_remove(const char* name);
void tn_cleanup(tid_t server);
