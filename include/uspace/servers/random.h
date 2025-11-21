/* random server protocol definitions */
#include <libs/prelude.h>

typedef enum _random_msg_type_t {
    RANDOM_GEN,
    RANDOM_GEN_WITH_SEED,
    RANDOM_GEN_RESP,
} random_msg_type_t;

typedef struct _random_msg_t {
    random_msg_type_t type;
    union {
        struct {
            usize seed;
        } gen_with_seed;
        struct {
            usize val;
        } gen_resp;
    };
} random_msg_t;
