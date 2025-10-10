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
    // so we just use a simple singly linked list.
    struct _slab_t* next;
    usize nfree;
    obj_t* free_list;
} slab_t;

#define OBJ_SLAB(obj) \
    ((slab_t*)PGDOWN((usize)(obj)))


typedef struct _kmem_cache_t {
    usize obj_size;
    usize slab_size; // how many objects in a slab
    slab_t* partial_slabs;
    slab_t* free_slabs;
    slab_t* full_slabs;
} kmem_cache_t;

kmem_cache_t kmem_cache_create(usize obj_size);
void kmem_cache_destroy(kmem_cache_t* cache);
void* kmem_cache_alloc(kmem_cache_t* cache);
void kmem_cache_free(kmem_cache_t* cache, void* obj);

#endif

#endif