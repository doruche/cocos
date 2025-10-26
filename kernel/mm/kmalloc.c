#include "kernel/mm/kmalloc.h"
#include "libs/assert.h"
#include "libs/log.h"
#include "kernel/mm/slab.h"
#include "libs/macros.h"
#include "libs/types.h"

static const usize kmalloc_config[] = {
    8, 16, 32, 64, 128, 256,
};

static usize ncaches = array_size(kmalloc_config);
static kmem_cache_t caches[array_size(kmalloc_config)];


void
kmalloc_init(void) {
    for (usize i = 0; i < ncaches; i++) {
        kmem_cache_create(&caches[i], "kmalloc_cache", kmalloc_config[i]);
    }
}

void*
kmalloc(usize size) {
    for (usize i = 0; i < ncaches; i++) {
        if (size <= caches[i].data_size) {
            return kmem_cache_alloc(&caches[i]);
        }
    }
    warn("kmalloc: size %d too large", size);
    return NULL;
}

void
kfree(void* ptr) {
    obj_t* obj = container_of(ptr, obj_t, data);
    slab_t* slab = OBJ_SLAB(obj);
    usize data_size = slab->cache->data_size;

    // find the right cache
    for (isize i = ncaches - 1; i >= 0; i--) {
        if (data_size <= caches[i].data_size) {
            kmem_cache_free(&caches[i], ptr);
            return;
        }
    }

    panic("kfree: cannot find cache for size %d", data_size);
}