/*
 * extent iteration
 * e.g. range-iter over 2-11 with chunk size 3 yields:
 *      [2, 3), [3, 6), [6, 9), [9, 11)
 */

#pragma once

#include "libs/prelude.h"

// [start, end)
typedef struct {
    usize start;
    usize end;
} range_t;
typedef result_t (*range_iter_callback_t)(
    const range_t* chunk,
    void* ctx
);
result_t range_iter(
    const range_t* range,
    usize chunk_size,
    range_iter_callback_t callback,
    void* ctx
);