/*
 * fixed size heap for simple memory management
 * no thread-safety is considered,
 * caller should ensure that only one thread accesses the heap at a time
 */

#include <libs/prelude.h>
#include <libs/hooks.h>
#include <uspace/ipc.h>
#include <uspace/task.h>

extern u8 __heap_start[];
extern u8 __heap_end[];
static usize heap_size = 0;

typedef union _blk_header_t {
    struct {
        usize size; /* total size minus header */
        union _blk_header_t* next;
    };
    u8 padding[16];
} blk_header_t;
static_assert(sizeof(blk_header_t) == 16);


static blk_header_t* free_list = NULL;

#define blk_header(ptr) \
    ((blk_header_t*)((u8*)(ptr) - sizeof(blk_header_t)))
#define blk_totalsz(blk) \
    ((blk)->size + sizeof(blk_header_t))

void
heap_init(void) {
    heap_size = (usize)(__heap_end - __heap_start);
    free_list = (blk_header_t*)__heap_start;
    free_list->size = heap_size - sizeof(blk_header_t);
    free_list->next = NULL;
}

void* __hook_impl
__malloc(usize size) {
    if (size == 0 || free_list == NULL) {
        return NULL;
    }
    usize aligned_size = align_up(size, sizeof(usize));
    blk_header_t* prev = NULL;
    blk_header_t* curr = free_list;
    while (curr != NULL) {
        if (curr->size >= aligned_size) {
            if (curr->size >= aligned_size + sizeof(blk_header_t) + 8) {
                /* split */
                blk_header_t* new_blk = (blk_header_t*)((u8*)curr + sizeof(blk_header_t) + aligned_size);
                new_blk->size = curr->size - aligned_size - sizeof(blk_header_t);
                new_blk->next = curr->next;
                if (prev == NULL) {
                    free_list = new_blk;
                } else {
                    prev->next = new_blk;
                }
                curr->size = aligned_size;
            } else {
                /* use the whole block */
                if (prev == NULL) {
                    free_list = curr->next;
                } else {
                    prev->next = curr->next;
                }
            }
            return (void*)((u8*)curr + sizeof(blk_header_t));
        } 
        prev = curr;
        curr = curr->next;
    }
    pr_warn("__malloc: out of memory");
    return NULL;
}

void __hook_impl
__free(void* ptr) {
    assert_ne(ptr, NULL);

    blk_header_t* blk = blk_header(ptr);

    /* we keep free_list sorted by address */
    blk_header_t* prev = NULL;
    blk_header_t* curr = free_list;
    while (curr != NULL && curr < blk) {
        prev = curr;
        curr = curr->next;
    }
    blk->next = curr;

    /* try to merge with adjacent free blocks */
    if (curr != NULL &&
        (u8*)blk + blk_totalsz(blk) == (u8*)curr) {
        blk->size += blk_totalsz(curr);
        blk->next = curr->next;
    }
    if (prev != NULL) {
        prev->next = blk;
        if ((u8*)prev + blk_totalsz(prev) == (u8*)blk) {
            prev->size += blk_totalsz(blk);
            prev->next = blk->next;
        }
    } else {
        free_list = blk;
    }
}

usize __hook_impl
__objsize(void* ptr) {
    if (ptr == NULL) {
        panic("__objsize: NULL pointer");
    }
    return blk_header(ptr)->size;
}
