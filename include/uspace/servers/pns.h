/* 
 * PNS(Port Name System) server protocol definitions
 * NOTE: To work with pns, an extra port with PORT_SEND right
 * should be attached in message header's aux_xfer field.
 * However, in normal p_call, the aux_xfer has already
 * been occupied by the temporary port for receiving response.
 * Therefore, we have to reuse the aux_xfer port for both
 * receiving response and transferring PORT_SEND right
 * to pns.
 * We'll provide such encapsulations here. So do not
 * use p_call directly with pns, it will cause a panic!
 */

#pragma once

#include <libs/prelude.h>

#define PNS_MAX_NAME_LEN 64

typedef enum _pns_msg_id_t {
    PNS_REQ_RESOLVE = 0,
    PNS_REQ_PUBLISH = 1,
    PNS_REQ_UNPUBLISH = 2,
} pns_msg_id_t;

typedef union _pns_msgbody_t {
    /* 
     * Ask pns to resolve a name to a port id.
     * On success, pns will return a port with PORT_SEND right
     * to the requester.
     */
    struct {
        char name[PNS_MAX_NAME_LEN];
    } resolve;
    struct {
        port_t port;
    } resolve_resp;
    /*
     * Ask pns to publish a name to a port id.
     * Port with PORT_SEND right should be attached
     * in message header.
     * On success, pns will return a secret key to
     * the publisher, which can be used to unpublish later.
     */
    struct {
        char name[PNS_MAX_NAME_LEN];
    } publish;
    struct {
        u64 key;
        bool success;
    } publish_resp;
    /*
     * Ask pns to unpublish a name.
     */
    struct {
        char name[PNS_MAX_NAME_LEN];
        u64 key;
    } unpublish;
    struct {
        bool success;
    } unpublish_resp;
} pns_msgbody_t;

typedef struct _pns_msg_t {
    union {
        struct {
            msg_hdr_t header;
            pns_msgbody_t body;
        };
        u8 padding[MSG_MAX_SIZE];
    };
} pns_msg_t;

static_assert(sizeof(pns_msg_t) == MSG_MAX_SIZE);
static_assert(offset_of(pns_msg_t, header) == 0);
