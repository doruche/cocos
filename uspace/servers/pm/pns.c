#include "pns.h"
#include <libs/prelude.h>
#include <libs/list.h>
#include <uspace/servers/pns.h>
#include <uspace/syscall.h>
#include <uspace/ipc.h>

#define PNS_MAX_SERVICES 256
static struct pn_entry pn_table[PNS_MAX_SERVICES];
static list_t pn_list;

static u64
key_gen(void) {
    static u64 next_key = 0;
    return ++next_key;
}

static result_t
pns_resolve(const char* name, port_t* out) {
    list_foreach(iter, &pn_list) {
        struct pn_entry* entry = container_of(iter, struct pn_entry, node);
        if (strcmp(entry->name, name) == 0) {
            *out = entry->port;
            return OK;
        }
    }
    return -ERR_NOENT;
}

static result_t
pns_publish(const char* name, port_t port, u64* out_key) {
    /* check if the service is already published */
    list_foreach(iter, &pn_list) {
        struct pn_entry* entry = container_of(iter, struct pn_entry, node);
        if (strcmp(entry->name, name) == 0) {
            return -ERR_EXIST;
        }
    }
    /* find an empty slot */
    for (usize i = 0; i < PNS_MAX_SERVICES; i++) {
        if (pn_table[i].port == PID_INVALID) {
            struct pn_entry* entry = &pn_table[i];
            strncpy(entry->name, name, PNS_MAX_NAME_LEN - 1);
            entry->name[PNS_MAX_NAME_LEN - 1] = '\0';
            entry->port = port;
            entry->key = key_gen();
            list_push_back(&pn_list, &entry->node);
            *out_key = entry->key;
            return OK;
        }
    }

    warn("pns: publish \"%s\" failed, service table full", name);
    return -ERR_NOSPC;
}

static result_t
pns_unpublish(const char* name, u64 key) {
    list_foreach(iter, &pn_list) {
        struct pn_entry* entry = container_of(iter, struct pn_entry, node);
        if (strcmp(entry->name, name) == 0) {
            if (entry->key != key) {
                return -ERR_PERM;
            }
            /* remove from list */
            entry->port = PID_INVALID;
            list_remove(&entry->node);
            return OK;
        }
    }
    return -ERR_NOENT;
}

void
pns_init(void) {
    list_init(&pn_list);
    for (usize i = 0; i < PNS_MAX_SERVICES; i++) {
        pn_table[i].port = PID_INVALID;
    }
    port_t pns_port = unwrap_err(sys_p_creat(PID_PNS));
    assert_eq(pns_port, PID_PNS);
}

result_t
pns_handle_msg(pns_msg_t* msg) {
    port_t reply_port = msg->header.aux_xfer.port;
    p_stat_t reply_port_stat;
    unwrap_err(sys_p_stat(reply_port, &reply_port_stat));
    if (!port_has_send(reply_port_stat.privs)) {
        warn("pns: received message with invalid reply port %ld", reply_port);
        return -ERR_PERM;
    }

    pns_msg_t resp_msg = {0};
    resp_msg.header.remote = reply_port;
    resp_msg.header.id = msg->header.id;
    resp_msg.header.aux_xfer.port = PID_INVALID;

    result_t ret = OK;

    switch (msg->header.id) {
        case PNS_RESOLVE:
            const char* name = msg->body.resolve.name;
            port_t resolve_port;
            ret = pns_resolve(name, &resolve_port);
            if (is_err(ret)) {
                resp_msg.body.resolve_resp.port = PID_INVALID;
            } else {
                resp_msg.body.resolve_resp.port = resolve_port;
                resp_msg.header.aux_xfer.port = resolve_port;
                resp_msg.header.aux_xfer.flags = PORT_SEND;
            }
            /* as pns, we should send asynchronously. but now we just reply directly */
            unwrap_err(p_send((untyped_msg_t*)&resp_msg));
            return OK;
        case PNS_PUBLISH:
            const char* pub_name = msg->body.publish.name;
            port_t pub_port = msg->header.aux_xfer.port;
            u64 pub_key;
            ret = pns_publish(pub_name, pub_port, &pub_key);
            if (is_err(ret)) {
                resp_msg.body.publish_resp.key = 0;
                resp_msg.body.publish_resp.success = false;
            } else {
                resp_msg.body.publish_resp.key = pub_key;
                resp_msg.body.publish_resp.success = true;
            }
            unwrap_err(p_send((untyped_msg_t*)&resp_msg));
            return OK;
        case PNS_UNPUBLISH:
            const char* unpub_name = msg->body.unpublish.name;
            u64 unpub_key = msg->body.unpublish.key;
            ret = pns_unpublish(unpub_name, unpub_key);
            if (is_err(ret)) {
                resp_msg.body.unpublish_resp.success = false;
            } else {
                resp_msg.body.unpublish_resp.success = true;
            }
            unwrap_err(p_send((untyped_msg_t*)&resp_msg));
            return OK;
        default:
            warn("pns: received message with unknown id %ld", msg->header.id);
            return -ERR_INVAL;
    }
}

