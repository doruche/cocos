/*
 * simple slab allocator
 * even in such a microkernel, we need do some dynamic memory allocation
 * for various purposes, e.g. managing lists of objects.
 * so we keep a small heap for kernel use.
 * 
 * NOTE we do not allow objects with size bigger than a page (4KB)
 * to be allocated from the slab allocator.
 */

#ifndef _K_MM_SLAB_H
#define _K_MM_SLAB_H 1

#ifndef __DEFONLY__

#include "libs/types.h"
#include "kernel/arch/mm.h"

typedef struct _obj_t {
    struct _obj_t* next;
    u8 data[0];
} obj_t;

#define OBJ_SIZE(data_size) (sizeof(obj_t) + (data_size))

// a slab is just a page containing this small header and a bunch of objects
typedef struct _slab_t {
    // we can't use intrusive list here because we are now
    // building the slab allocator itself, and list_t depends on
    // dynamic memory allocation.
    // so we just use a simple double linked list.
    struct _slab_t* prev;
    struct _slab_t* next;
    usize data_size; // object without header
    usize nfree;
    usize nobj; // total number of objects
    obj_t* free_list;
} slab_t;

#define OBJ_SLAB(obj) \
    ((slab_t*)PGDOWN((usize)(obj)))


typedef struct _kmem_cache_t {
    usize data_size; // object without header
    // sentinel nodes for slab lists
    slab_t* partial_slabs; // slabs with some free objects
    slab_t* free_slabs; // slabs with all objects free
    slab_t* full_slabs; // slabs with no free objects
} kmem_cache_t;

kmem_cache_t    kmem_cache_create(usize data_size);
void            kmem_cache_destroy(kmem_cache_t* cache);
void*           kmem_cache_alloc(kmem_cache_t* cache);
void            kmem_cache_free(kmem_cache_t* cache, void* obj);

void            kmem_cache_dump(kmem_cache_t* cache);

#endif

#endif