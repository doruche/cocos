/*
 * dynamic arrays.
 * much more lightweight than intrusive list.
 */

#include "libs/prelude.h"

typedef struct _vec_t {
    usize capacity;
#define VEC_INIT_CAPACITY 4
    usize elem_size;
    usize len;
    u8* elements;
} vec_t;

void    vec_init(vec_t* vec, usize elem_size);
void    vec_get(const vec_t* vec, usize idx, void* elem);
void    vec_insert(vec_t* vec, usize idx, const void* elem);
void    vec_remove(vec_t* vec, usize idx, void* elem);
void    vec_destroy(vec_t* vec);

#define vec_len(vec) \
    ((vec)->len)
#define vec_push(vec, elem) \
    vec_insert((vec), (vec)->len, ((const void*)(elem)))
#define vec_pop(vec, elem) \
    vec_remove((vec), (vec)->len - 1, ((void*)(elem)))

// do not allow modifying the vector during iteration!
#define vec_foreach(iter, vec, type) \
    for (\
        usize _i = 0; \
        (iter) = ((type*)((vec)->elements)) + _i, \
        _i < (vec)->len; \
        _i++ \
    )
