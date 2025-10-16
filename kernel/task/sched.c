#include "kernel/arch/ctx.h"
#include "kernel/task/sched.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "libs/types.h"
#include "libs/list.h"
#include "kernel/mm/slab.h"

static list_t task_list;

static tid_t next_tid = 0;

static kmem_cache_t task_cache;

__maybe_unused
static tid_t
alloc_tid() {
    // refine later to avoid tid overflow
    return next_tid++;
}

void
task_init() {
    list_init(&task_list);
    task_cache = kmem_cache_create(sizeof(task_t));
}

task_t*
task_spawn(void (*entry)(void)) {
    task_t* task = kmem_cache_alloc(&task_cache);
    assert(task != NULL);
    todo()
}

