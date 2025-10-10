#include "kernel/mm/pm.h"
#include "kernel/mm/slab.h"
#include "kernel/consts/params.h"
#include "kernel/misc/assert.h"
#include "kernel/misc/log.h"
#include "libs/macros.h"

/// if this exceeds KERNEL_HEAP_SIZE, we panic.
static usize nused_pages = 0;

static void
slab_init(slab_t* slab, usize data_size) {
    // PAGE_SIZE
    // |slab_header|pad0|obj1|pad|obj2|pad|obj3|pad|...|
    usize aligned_obj_size = align_up(OBJ_SIZE(data_size), 8);
    usize aligned_header_size = align_up(sizeof(slab_t), 8);
    u8* alloc_start = (u8*)slab + aligned_header_size;
    usize nobj = (PAGE_SIZE - aligned_header_size) / aligned_obj_size;
    slab->nfree = nobj;

    // init free list
    for (usize i = 0; i < nobj; i++) {
        obj_t* obj = (obj_t*)(alloc_start + i * aligned_obj_size);
        obj->next = slab->free_list;
        slab->free_list = obj;
    }
    slab->next = NULL;
}

kmem_cache_t
kmem_cache_create(usize obj_size) {
    assert(obj_size > 0 && obj_size <= PAGE_SIZE);
    
    // lazy implementation, we do not allocate any memory now.
    kmem_cache_t cache;
    cache.obj_size = obj_size;
    cache.slab_size = PAGE_SIZE / obj_size;
    cache.partial_slabs = NULL;
    cache.free_slabs = NULL;
    cache.full_slabs = NULL;

    return cache;
}

void*
kmem_cache_alloc(kmem_cache_t* cache) {
    assert(cache != NULL);

    slab_t* slab = NULL;

    // we tend to use free slabs first, then partial slabs.
    if (cache->free_slabs) {
        slab = cache->free_slabs;
        cache->free_slabs = slab->next;
    } else if (cache->partial_slabs) {
        slab = cache->partial_slabs;
        cache->partial_slabs = slab->next;
        // we'll move it to partial_slabs again if it is still partial after allocation
    } else {
        // need to allocate a new slab
        nused_pages++;
        if (nused_pages >= KERNEL_HEAP_SIZE / PAGE_SIZE) {
            panic("kmem_cache_alloc: out of memory");
        }
        ppn_t ppn = palloc();
        if (ppn == 0) {
            panic("kmem_cache_alloc: palloc failed");
        }
        slab = (slab_t*)PPN2PA(ppn);
        slab_init(slab, cache->obj_size);
    }

    if (slab) {
        // allocate an object from the slab
        obj_t* obj = slab->free_list;
        slab->free_list = obj->next;
        slab->nfree--;
        if (slab->nfree == 0) {
            // move to full_slabs
            slab->next = cache->full_slabs;
            cache->full_slabs = slab;
        } else {
            // move to partial_slabs
            slab->next = cache->partial_slabs;
            cache->partial_slabs = slab;
        }
        return obj->data;
    } else {
        unreachable();
    }
}

void
kmem_cache_free(kmem_cache_t* cache, void* data) {
    obj_t* obj = container_of(data, obj_t, data);
    slab_t* slab = OBJ_SLAB(obj);
    slab->nfree++;
    obj->next = slab->free_list;
    slab->free_list = obj;
}

void
kmem_cache_destroy(kmem_cache_t* cache) {
    // why would we want to destroy a cache?
    unreachable();
}