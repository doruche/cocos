#include "libs/prelude.h"
#include "libs/vec.h"
#include "libs/mm.h"

void
vec_init(vec_t* vec, usize elem_size) {
    vec->capacity = VEC_INIT_CAPACITY;
    vec->elem_size = elem_size;
    vec->len = 0;
    vec->elements = unwrap_null(calloc(VEC_INIT_CAPACITY, elem_size));
}

// todo