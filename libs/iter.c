#include "libs/prelude.h"
#include "libs/iter.h"

isize
range_iter(
    const range_t* range,
    usize chunk_size,
    range_iter_callback_t callback,
    void* ctx
) {
    usize current = range->start;
    while (current < range->end) {
        usize end = min(
            align_down(current, chunk_size) + chunk_size,
            range->end
        );
        isize ret = callback(
            &(range_t){
                .start = current,
                .end = end
            },
            ctx
        );
        if (is_err(ret)) {
            // should we provide a cleanup callback parameter here?
            // anyway too complex for now
            return ret;
        }
        current = end;
    }
    return 0;
}