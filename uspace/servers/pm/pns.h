#pragma once
#include <libs/prelude.h>
#include <libs/list.h>
#include <uspace/servers/pns.h>

struct pn_entry {
    char name[PNS_MAX_NAME_LEN];
    port_t port;
    u64 key;
    list_elem_t node;    
};

void        pns_init(void);
result_t    pns_handle_msg(pns_msg_t* msg);
