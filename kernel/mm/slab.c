#include "kernel/mm/pm.h"
#include "kernel/mm/slab.h"
#include "kernel/consts/params.h"
#include "kernel/misc/assert.h"
#include "kernel/misc/log.h"
#include "libs/macros.h"
#include "libs/string.h"

#define sentinel_init(name) ((slab_t){ &(name), &(name), 0, 0, 0, NULL })

static bool
is_slabs_empty(slab_t* list) {
    return (slab_t*)list->next == list;
}

static void
slab_insert(slab_t* prev, slab_t* next, slab_t* slab) {
    prev->next = slab;
    next->prev = slab;
    slab->prev = prev;
    slab->next = next;
}

static void
slab_push_back(slab_t* list, slab_t* slab) {
    slab_insert(list->prev, list, slab);
}

static void
slab_remove(slab_t* list, slab_t* slab) {
    slab->prev->next = slab->next;
    slab->next->prev = slab->prev;
    slab->prev = NULL;
    slab->next = NULL;
}

static slab_t*
slab_pop_front(slab_t* list) {
    if (is_slabs_empty(list)) {
        return NULL;
    }
    slab_t* slab = list->next;
    slab_remove(list, slab);
    return slab;
}

// init inner data.
// caller responsible for creating links.
static void
slab_init(kmem_cache_t* cache, slab_t* slab) {
    // PAGE_SIZE
    // |slab_header|pad0|obj1|pad|obj2|pad|obj3|pad|...|
    usize data_size = cache->data_size;
    usize aligned_obj_size = align_up(OBJ_SIZE(data_size), 8);
    usize aligned_header_size = align_up(sizeof(slab_t), 8);
    u8* alloc_start = (u8*)slab + aligned_header_size;
    usize nobj = (PAGE_SIZE - aligned_header_size - 1) / aligned_obj_size; // question: why minus 1?
    slab->cache = cache;
    slab->nfree = nobj;
    slab->nobj = nobj;
    
    // init free list
    slab->free_list = NULL;
    for (usize i = 0; i < nobj; i++) {
        obj_t* obj = (obj_t*)(alloc_start + i * aligned_obj_size);
        obj->next = slab->free_list;
        slab->free_list = obj;
    }
    
    slab->next = NULL;
    slab->prev = NULL;


#ifdef DEBUG
    info("slab_init: initialized slab %p for cache %s", slab, cache->name);
    info("slab_init: addr=%p, data_size=%d, nobj=%d", slab, data_size, nobj);
    info("slab_init: first obj at %p", alloc_start);
    info("slab_init: last obj at %p", alloc_start + (nobj - 1) * aligned_obj_size);
#endif
}

void
kmem_cache_create(kmem_cache_t* cache, const char* name, usize data_size) {
    assert(data_size > 0 && OBJ_SIZE(data_size) <= PAGE_SIZE);
    
    // lazy implementation, we do not allocate any memory now.
    strncpy(cache->name, name, KMEM_CACHE_NAME_MAX_LEN - 1);
    cache->name[KMEM_CACHE_NAME_MAX_LEN - 1] = '\0';
    cache->data_size = data_size;
    cache->partial_slabs = sentinel_init(cache->partial_slabs);
    cache->free_slabs = sentinel_init(cache->free_slabs);
    cache->full_slabs = sentinel_init(cache->full_slabs);

    trace("kmem_cache_create: cache %s created data_size %d", cache->name, cache->data_size);
}

void*
kmem_cache_alloc(kmem_cache_t* cache) {
    assert(cache != NULL);

    slab_t* slab = NULL;

    // we tend to use free slabs first, then partial slabs.
    if (!is_slabs_empty(&cache->free_slabs)) {
        // we'll move it to partial_slabs again if it is still partial after allocation
        slab = slab_pop_front(&cache->free_slabs);
    } else if (!is_slabs_empty(&cache->partial_slabs)) {
        slab = slab_pop_front(&cache->partial_slabs);
    } else {
        // need to allocate a new slab
        warn("kmem_cache_alloc: allocating new slab");
        ppn_t ppn = unwrap_err(pm_alloc());
        slab = (slab_t*)PN2PA(ppn);
        slab_init(cache, slab);
    }

    if (slab) {
        // allocate an object from the slab
        obj_t* obj = slab->free_list;
        assert_ne(obj, NULL);

        slab->free_list = obj->next;
        slab->nfree--;
        if (slab->nfree == 0) {
            slab_push_back(&cache->full_slabs, slab);
        } else {
            slab_push_back(&cache->partial_slabs, slab);
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

    if (slab->nfree == 1) {
        // was full, now partial
        // remove from full_slabs
        slab_remove(&cache->full_slabs, slab);
        // we tend to distribute allocations across slabs,
        // so we push it to the back of partial_slabs
        slab_push_back(&cache->partial_slabs, slab);
    } else if (slab->nfree == slab->nobj) {
        // was partial, now free
        slab_remove(&cache->partial_slabs, slab);
        slab_push_back(&cache->free_slabs, slab);
    }
}

void
kmem_cache_destroy(kmem_cache_t* cache) {
    // why would we want to destroy a cache?
    unreachable();
}

void
kmem_cache_dump(kmem_cache_t* cache) {
    usize nfree = 0, npartial = 0, nfull = 0;
    slab_t* cur;

    cur = cache->free_slabs.next;
    while (cur != &cache->free_slabs) {
        nfree++;
        cur = cur->next;
    }

    cur = cache->partial_slabs.next;
    while (cur != &cache->partial_slabs) {
        npartial++;
        cur = cur->next;
    }

    cur = cache->full_slabs.next;
    while (cur != &cache->full_slabs) {
        nfull++;
        cur = cur->next;
    }

    info("kmem_cache_dump: data_size=%d, free_slabs=%d, partial_slabs=%d, full_slabs=%d",
        cache->data_size, nfree, npartial, nfull);
}