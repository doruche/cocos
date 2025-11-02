#include "kernel/arch/ctx.h"
#include "kernel/task/sched.h"
#include "kernel/ipc.h"
#include "libs/prelude.h"
#include "libs/list.h"
#include "kernel/mm/slab.h"
#include "kernel/mm/vm.h"
#include "kernel/consts/params.h"
#include "kernel/arch/board.h"
#include "kernel/task/processor.h"
#include "kernel/arch/timer.h"
#include "kernel/arch/csr.h"
#include "kernel/trap.h"
#include "kernel/boot.h"
#include "kernel/mm/pm.h"
#include "libs/elf.h"
#include "kernel/mm/kmalloc.h"

static list_t all_tasks; // all tasks
// tasks in READY / RUNNING / ZOMBIE state
// keep ZOMBIE here for simple cleanup. refine later.
static list_t running_tasks;

static tid_t next_tid = 1;

static kmem_cache_t task_cache;
static kmem_cache_t task_vms_cache;
static kmem_cache_t task_actx_cache;

static tid_t
alloc_tid() {
    // reserve zero for non-existent task
    // refine later to avoid tid overflow
    return next_tid++;
}

__maybe_unused
task_t*
task_get(tid_t tid) {
    list_foreach(iter, &all_tasks) {
        task_t* task = list_entry(iter, task_t, node_all);
        if (task->tid == tid) {
            return task;
        }
    }
    return NULL;
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

// create pm task from boot image and
// push it into both all_tasks and running_tasks list
static void
creat_first_task(u8* bootimage) {
    elf_hdr_t* elf_header = (elf_hdr_t*)bootimage;
    if (memcmp(elf_header->e_ident, ELF_MAGIC, 4) != 0) {
        panic("creat_first_task: invalid elf magic");
    }

    task_t* init_task = task_spawn("pm", elf_header->e_entry, 0);

    // load program segments
    elf_phdr_t* phdrs = (elf_phdr_t*)(bootimage + elf_header->e_phoff);
    for (usize i = 0; i < elf_header->e_phnum; i++) {
        elf_phdr_t* phdr = &phdrs[i];
        if (phdr->p_type != PT_LOAD) {
            continue;
        }

        vm_flags_t flags = VM_USER;
        if (phdr->p_flags & PF_R) {
            flags |= VM_READ;
        }
        if (phdr->p_flags & PF_W) {
            flags |= VM_WRITE;
        }
        if (phdr->p_flags & PF_X) {
            flags |= VM_EXEC;
        }

        usize memsz = phdr->p_memsz;
        usize filesz = phdr->p_filesz;
        usize npages = PGUP(memsz) / PAGE_SIZE;
        
        unwrap_err(vm_alloc(
            init_task->vms,
            (vpn_t)PA2PN(phdr->p_vaddr),
            npages,
            flags
        ));
        unwrap_err(vm_memcpy(
            init_task->vms,
            phdr->p_vaddr,
            (kaddr_t)(bootimage + phdr->p_offset),
            filesz
        ));
        unwrap_err(vm_memset(
            init_task->vms,
            phdr->p_vaddr + filesz,
            0,
            memsz - filesz
        ));
        info("loaded init task segment: vaddr=%p memsz=%ld filesz=%ld flags=%c%c%c",
            phdr->p_vaddr, memsz, filesz,
            (flags & VM_READ) ? 'r' : '-',
            (flags & VM_WRITE) ? 'w' : '-',
            (flags & VM_EXEC) ? 'x' : '-'
        );
    }

    task_resume(init_task->tid);

    notify("first task created: tid=%ld name=%s",
        init_task->tid, init_task->name);
    notify("free pages after creating first task: %ld", pm_count_free());
}

void
sched_init(u8* init_elf) {
    list_init(&all_tasks);
    list_init(&running_tasks);
    kmem_cache_create(&task_cache, "task_cache", sizeof(task_t));
    kmem_cache_create(&task_vms_cache, "task_vms_cache", sizeof(vm_space_t));
    kmem_cache_create(&task_actx_cache, "task_actx_cache", sizeof(arch_ctx_t));

    // must init processor before creating first task.
    // there are dependencies between their mappings.
    processor_init();
    notify("free pages after processor init: %ld", pm_count_free());
    creat_first_task(init_elf);

    // declare an unused ctx on boot stack
    ctx_t place_holder;
    ctx_switch(&place_holder, scheduler_ctx);
}

// create a new task, pushing it into all_tasks.
// should call task_resume to make it runnable.
// we do not handle any user space memory manipulation except for 
// user stack here,
// they will be done by process manager.:P
// p.s. user stacks should be allocated by process manager too.
// refine later.
task_t*
task_spawn(const char* name, uaddr_t entry, port_t pager) {
    task_t* task = unwrap_null(kmem_cache_alloc(&task_cache));
    memset(task, 0, sizeof(task_t));

    task->tid = alloc_tid();
    strncpy(task->name, name, TASK_NAME_MAX_LEN);
    task->state = T_BLOCKED;
    
    // W.I.P. pager

    task->vms = unwrap_null(kmem_cache_alloc(&task_vms_cache));
    vm_init(task->vms);
    // important point:
    // we copy scheduler page table as the base of new task page table.
    // this is convenient, as well as easy for kernel to access user space memory.
    // this include:
    // 1. kernel code   necessary
    // 2. free memory   necessary
    // 3. trampoline    necessary
    // 4. scheduler kstack. can be avoided by assembly tricks, but whatever.
    kvms_derive(task->vms);

    // initialize arch context
    task->actx = unwrap_null(kmem_cache_alloc(&task_actx_cache));
    kaddr_t mapped_kstack_top = task_kstack_top(task->tid);
    actx_init(
        task->actx,
        task->vms,
        mapped_kstack_top,
        (kaddr_t)utrap_ret,
        entry
    );

    task->alloced_pages = unwrap_null(
        kmalloc(sizeof(ppn_t) * TASK_MAX_PHYS_PAGES)
    );
    memset(
        task->alloced_pages,
        0,
        sizeof(ppn_t) * TASK_MAX_PHYS_PAGES
    );

    list_push_back(&all_tasks, &task->node_all);

    // ipc_init
    // should make this a separate function later.
    list_init(&task->port_list); 


    info("task spawned: tid=%ld name=%s entry=%p",
        task->tid, task->name, (void*)entry);

    return task;
}

// block a task.
// if the task is the caller itself, yield cpu immediately.
void
task_block(tid_t tid) {
    task_t* task = unwrap_null(task_get(tid));
    trace("task_block: blocking task tid=%ld name=%s",
        task->tid, task->name);
    assert_ne(task->state, T_BLOCKED);
    task->state = T_BLOCKED;
    list_remove(&task->node_running);

    if (task == current_task) {
        ctx_switch(
            &task->actx->ctx,
            scheduler_ctx
        );
    }
}


void
task_resume(tid_t tid) {
    task_t* task = unwrap_null(task_get(tid));
    trace("task_resume: resuming task tid=%ld name=%s",
        task->tid, task->name);
    assert_eq(task->state, T_BLOCKED);
    task->state = T_READY;
    list_push_back(&running_tasks, &task->node_running);
}

/*
 * we have 2 ways to exit a task:
 * 1. sys_exit() called by process manager.
 *    in this case, we can free all resources immediately.
 * 2. task itself crashes (illegal instruction, page fault, etc).
 *    in this case, we cannot free resources right now,
 *    as we're still on the task's kernel stack.
 *    we just mark the task as ZOMBIE here,
 *    and let the scheduler free it later.
 */

static void
task_cleanup(task_t* task) {
    list_remove(&task->node_all);
    if (task->state != T_BLOCKED) {
        list_remove(&task->node_running);
    }

    for (usize i = 0; i < TASK_MAX_PHYS_PAGES; i++) {
        ppn_t ppn = task->alloced_pages[i];
        if (ppn != 0) {
            assert(pm_decref(ppn));
        }
    }

    // todo: port cleanup

    actx_destroy(task->actx, task->vms);
    vm_destroy(task->vms);
    kmem_cache_free(&task_vms_cache, task->vms);
    kmem_cache_free(&task_actx_cache, task->actx);
    kmem_cache_free(&task_cache, task);
}

// from process manager's sys_kill
// way to finish a task gracefully
void
task_kill(tid_t tid) {
    task_t* task = unwrap_null(task_get(tid));
    assert_ne(task, current_task);
    assert(task->state == T_READY || task->state == T_BLOCKED);
    // no need to switch to T_ZOMBIE.
    task_cleanup(task);
    info("task gracefully killed: tid=%ld name=%s",
        task->tid, task->name);
}

// from illegal behavior
// or task killing itself
// should send a message to process manager later.
void
task_crash_exit(void) {
    task_t* current = unwrap_null(current_task);
    if (current->tid == TID_PM) {
        panic("pm server crashed!");
    }
    
    assert_eq(current->state, T_RUNNING);
    current->state = T_ZOMBIE;
    ctx_switch(
        &current->actx->ctx,
        scheduler_ctx
    );
}

// called on process context.
// give up cpu and switch to scheduler.
void
task_yield(void) {
    task_t* current = unwrap_null(current_task);
    assert_eq(current->state, T_RUNNING);
    current->state = T_READY;
    ctx_switch(
        &current->actx->ctx,
        scheduler_ctx
    );
}

static void
task_dump(void) {
    info("==== task dump start ====");
    list_foreach(iter, &all_tasks) {
        task_t* task = list_entry(iter, task_t, node_all);
        info("task tid=%ld name=%s state=%d",
            task->tid, task->name, task->state);
        list_foreach(port_iter, &task->port_list) {
            task_port_t* tport = list_entry(port_iter, task_port_t, node);
            ipc_port_t* port = unwrap_null(p_get(tport->id));
            info("  port id=%ld privs=%lx dead=%d tx_rc=%ld",
                tport->id, tport->privs, port->dead, port->tx_rc);
        }
    }
    info("==== task dump end ====");
}

void
scheduler(void) {
    // currently just simple round-robin
    assert(intr_enabled());

    loop {
        list_foreach_safe(iter, &running_tasks, next) {
            task_t* task = list_entry(iter, task_t, node_running);
            trace("sched: considering task tid=%ld name=%s state=%d",
                task->tid, task->name, task->state);
            if (task->state == T_READY) {
                task->state = T_RUNNING;
                current_task = task;

                vm_activate(task->vms);
                trace("sched: switching to task tid=%ld name=%s",
                    task->tid, task->name);
                ctx_switch(
                    scheduler_ctx,
                    &task->actx->ctx
                );

                // returned from task
                extern vm_space_t kernel_vms;
                vm_activate(&kernel_vms);
                current_task = NULL;
                assert_ne(task->state, T_RUNNING); // should be managed by various ways
            } else if (task->state == T_ZOMBIE) {
                task_cleanup(task);
                trace("zombie task cleaned up: tid=%ld name=%s",
                    task->tid, task->name);
            } else {
                unreachable();
            }
        }
        trace("sched: one full round done.");
        trace("free pages: %ld", pm_count_free());
        set_timer(5);
        wait_for_intr();
        task_dump();
    }
}