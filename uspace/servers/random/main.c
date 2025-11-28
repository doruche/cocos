#include <libs/prelude.h>
#include <uspace/ipc.h>

static usize
random_gen(usize seed) {
    /* just a simple PCG */
    static usize state = 0x4B414655;
    static usize inc = 0x4A4F5543484F;

    state = state * 6364136223846793005ULL + (inc | 1);
    usize xorshifted = ((state >> 18u) ^ state) >> 27u;
    usize rot = state >> 59u;
    usize result = (xorshifted >> rot) | (xorshifted << ((-rot) & 31));

    return result ^ seed;
}

result_t
main(void) {
    unwrap_err(pns_publish("random"));
    pr_info("random server started.");

    loop {
        msg_t msg = {0};
        result_t ret = ipc_recv(IPC_OPEN, &msg);
        if (is_err(ret)) {
            pr_warn("random: ipc_recv failed: %s",
                strerr(ret));
            continue;
        }
        msg_t resp = {0};

        switch (msg.type) {
            case MSG_RANDOM: {
                switch (msg.random.type) {
                    case RANDOM_GEN: {
                        usize val = random_gen(0);
                        resp.random.type = RANDOM_GEN_RESP;
                        resp.random.gen_resp.val = val;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    case RANDOM_GEN_WITH_SEED: {
                        usize val = random_gen(
                            msg.random.gen_with_seed.seed
                        );
                        resp.random.type = RANDOM_GEN_RESP;
                        resp.random.gen_resp.val = val;
                        rpc_reply(msg.src, &resp);
                        break;
                    }
                    default: {
                        pr_warn("random: unknown random msg type %ld from %ld",
                            msg.random.type, msg.src);
                        break;
                    }
                }
                break;
            }
            default: {
                pr_warn("random: received unknown msg type %ld from %ld",
                    msg.type, msg.src);
                break;
            }
        }
    }

    pr_info("random server exiting.");
    return OK;
}
