#include "libs/prelude.h"
#include "libs/mm.h"
#include "libs/hooks.h"

void*
malloc(usize size) {
    return hook_call(malloc, size);
}

void
free(void* ptr) {
    hook_call(free, ptr);
}

void*
realloc(void* ptr, usize new_size) {
    void* new_ptr = malloc(new_size);
    if (new_ptr == NULL) {
        return NULL;
    }
    usize old_size = hook_call(objsize, ptr);
    usize to_copy = min(new_size, old_size);
    memcpy(new_ptr, ptr, to_copy);
    free(ptr);
    return new_ptr;    
}

void*
calloc(usize num, usize size) {
    usize total_size = num * size;
    void* ptr = malloc(total_size);
    if (ptr == NULL) {
        return NULL;
    }
    memset(ptr, 0, total_size);
    return ptr;
}