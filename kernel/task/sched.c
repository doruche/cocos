#include "kernel/arch/ctx.h"
#include "kernel/task/sched.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "libs/macros.h"
#include "libs/types.h"
#include "libs/list.h"
#include "kernel/mm/slab.h"
#include "kernel/mm/vm.h"
#include "kernel/consts/params.h"
#include "kernel/arch/board.h"
#include "kernel/task/processor.h"
#include "kernel/arch/timer.h"
#include "kernel/arch/csr.h"

static list_t task_list;

static tid_t next_tid = 0;

static kmem_cache_t task_cache;

__maybe_unused
static tid_t
alloc_tid() {
    // refine later to avoid tid overflow
    return next_tid++;
}

kaddr_t
task_kstack_top(tid_t tid) {
    kaddr_t top = TRAMPOLINE;
    // scheduler
    top -= (KSTACK_SIZE + PAGE_SIZE);
    // tasks
    top -= tid * (KSTACK_SIZE + PAGE_SIZE);
    return top;
}

static void
creat_first_task(void) {
    todo()
}

void
sched_init() { 
    extern vm_space_t kernel_vms;
    vm_dump(&kernel_vms);

    list_init(&task_list);
    task_cache = kmem_cache_create(sizeof(task_t));
    creat_first_task();

    processor_init();

    // declare an unused ctx on boot stack
    ctx_t place_holder;
    ctx_switch(&place_holder, scheduler_ctx);
}

task_t*
task_spawn(void (*entry)(void)) {
    task_t* task = kmem_cache_alloc(&task_cache);
    assert(task != NULL);
    todo()
}

void
sched(void) {
    // currently just simple round-robin
    assert(intr_enabled());

    loop {
        list_foreach_safe(iter, &task_list, next) {
            __maybe_unused task_t* task = list_entry(iter, task_t, node);
            todo();            
        }
        trace("sched: one full round done.");
        set_timer(10);
        wait_for_intr();
    }
}