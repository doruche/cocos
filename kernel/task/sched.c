#include <libs/prelude.h>
#include <libs/list.h>
#include <libs/elf.h>
#include <kernel/arch/arch.h>
#include <kernel/task/sched.h>
#include <kernel/ipc.h>
#include <kernel/mm/slab.h>
#include <kernel/mm/as.h>
#include <kernel/consts/params.h>
#include <kernel/task/processor.h>
#include <kernel/mm/pm.h>
#include <kernel/mm/kmalloc.h>

/*
 * Invariable we should keep during scheduling:
 * 1. current_task != NULL  <=>  cpu is in task context, not scheduler context.
 * 2. current_task cannot be a T_BLOCKED or T_ZOMBIE task.
 * 3. running_tasks list only contains T_READY / T_RUNNING / T_ZOMBIE tasks.
 */

static list_t all_tasks;
static list_t running_tasks;
static list_t zombie_tasks;

static tid_t next_tid = TID_PM;

static kmem_cache_t task_cache;

static task_t* pm = NULL;

static tid_t
alloc_tid() {
    if (next_tid == TID_INVALID) {
        panic("alloc_tid: out of tids");
    }
    return next_tid++;
}

result_t
task_get(tid_t tid, task_t** out) {
    list_foreach(iter, &all_tasks) {
        task_t* task = list_entry(iter, task_t, node_all);
        if (task->tid == tid) {
            *out = task;
            return OK;
        }
    }
    return -ERR_NOENT;
}

vpn_t
task_kstack_top(tid_t tid) {
    kaddr_t top = arch_vm_topaddr();
    // kstack with guard page
    top -= tid * (KSTACK_SIZE + PAGE_SIZE) / PAGE_SIZE;
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

    task_t* init_task = NULL;
    unwrap_err(task_spawn(
        "pm", 
        elf_header->e_entry, 
        ASID_NEW,
        &init_task
    ));

    // load program segments
    elf_phdr_t* phdrs = (elf_phdr_t*)(bootimage + elf_header->e_phoff);
    for (usize i = 0; i < elf_header->e_phnum; i++) {
        elf_phdr_t* phdr = &phdrs[i];
        if (phdr->p_type != PT_LOAD) {
            continue;
        }

        vm_flags_t flags = VM_USER | VM_ANON;
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
        
        unwrap_err(as_map(
            init_task->as,
            (vpn_t)PA2PN(phdr->p_vaddr),
            (ppn_t)PPN_ANON,
            npages,
            flags
        ));
        unwrap_err(as_memcpy(
            init_task->as,
            phdr->p_vaddr,
            bootimage + phdr->p_offset,
            filesz
        ));
        unwrap_err(as_memset(
            init_task->as,
            phdr->p_vaddr + filesz,
            0,
            memsz - filesz
        ));
        pr_info("loaded init task segment: vaddr=%p memsz=%ld filesz=%ld flags=%c%c%c",
            phdr->p_vaddr, memsz, filesz,
            (flags & VM_READ) ? 'r' : '-',
            (flags & VM_WRITE) ? 'w' : '-',
            (flags & VM_EXEC) ? 'x' : '-'
        );
    }

    task_resume(init_task->tid);
    pm = init_task;

    pr_notify("first task created: tid=%ld name=%s",
        init_task->tid, init_task->name);
    pr_notify("free pages after creating first task: %ld", pm_count_free());
}

void __noreturn
sched_init(u8* init_elf) {
    list_init(&all_tasks);
    list_init(&running_tasks);
    list_init(&zombie_tasks);
    kmem_cache_create(&task_cache, "task_cache", sizeof(task_t));

    processor_init();
    pr_notify("free pages after processor init: %ld", pm_count_free());
    creat_first_task(init_elf);

    arch_kctx_load(scheduler_ctx);
    unreachable();
}

// create a new task, pushing it into all_tasks.
// should call task_resume to make it runnable.
// we do not handle any user space memory manipulation except for 
// user stack here,
// they will be done by process manager.:P
// p.s. user stacks should be allocated by process manager too.
// refine later.
result_t
task_spawn(
    const char* name, 
    uaddr_t entry, 
    asid_t asid,
    task_t** out
) {
    task_t* task = unwrap_null(kmem_cache_alloc(&task_cache));
    memset(task, 0, sizeof(task_t));

    task->tid = alloc_tid();
    strncpy(task->name, name, TASK_NAME_MAX_LEN);
    task->state = T_BLOCKED;

    if (asid == ASID_NEW) {
        as_creat(task);
    } else {
        addr_space_t* as = NULL;
        if (is_err(as_get(asid, &as))) {
            kmem_cache_free(&task_cache, task);
            pr_warn("task_spawn: no such address space %ld", asid);
            return -ERR_NOENT;
        }
        as_bind(as, task);
    }
    
    // initialize arch context
    vpn_t kstack_top = task_kstack_top(task->tid);
    task->actx = unwrap_null(arch_ctx_creat(
        task->as->arch_vm,
        (kaddr_t)arch_utrap_ret,
        entry,
        kstack_top
    ));

    list_push_back(&all_tasks, &task->node_all);

    // ipc_init
    list_init(&task->sender_list);
    list_init(&task->receiver_list);
    task->listen_on = TID_INVALID;

    *out = task;
    pr_info("task spawned: tid=%ld name=%s entry=%p",
        task->tid, task->name, (void*)entry);

    return OK;
}

// block a task.
// if the task is the caller itself, yield cpu immediately.
result_t
task_block(tid_t tid) {
    task_t* task = NULL;
    if (is_err(task_get(tid, &task))) {
        pr_warn("task_block: no such task %ld", tid);
        return -ERR_NOENT;
    }
    pr_trace("task_block: blocking task tid=%ld name=%s",
        task->tid, task->name);

    /* CRITICAL SECTION START */
    assert_ne(task->state, T_BLOCKED);
    task->state = T_BLOCKED;
    list_remove(&task->node_running);
    if (task == current_task) {
        arch_kctx_switch(
            arch_ctx_kctx(current_task->actx),
            scheduler_ctx
        );
    }
    /* CRITICAL SECTION END */

    return OK;
}


result_t
task_resume(tid_t tid) {
    task_t* task = NULL;
    if (is_err(task_get(tid, &task))) {
        pr_warn("task_resume: no such task %ld", tid);
        return -ERR_NOENT;
    }
    if (task->state != T_BLOCKED) {
        pr_warn("task_resume: task tid=%ld name=%s not blocked",
            task->tid, task->name);
        return -ERR_INVAL;
    }
    pr_trace("task_resume: resuming task tid=%ld name=%s",
        task->tid, task->name);
    task->state = T_READY;
    list_push_back(&running_tasks, &task->node_running);
    return OK;
}

/*
 * the way we handle task exiting:
 * 1. a task called sys_task_exit.
 *  kernel then reclaims almost all resources of the task,
 *  but leaves a minimal task structure as a zombie with
 *  necessary metadata (tid, exit code) for the process manager to collect.
 *  finally, the kernel sends a exception message to the pm task.
 * 2. pm task receives the exit message, collects all the data
 *  it needs, then calls sys_task_destroy on the exited task.
 * 3. kernel reclaims all remaining resources of the task.
 */

result_t
task_destroy(tid_t tid) {
    task_t* task = NULL;
    if (is_err(task_get(tid, &task))) {
        pr_warn("task_destroy: no such task %ld", tid);
        return -ERR_NOENT;
    }

    assert_eq(task->state, T_ZOMBIE);
    list_remove(&task->node_all);
    list_remove(&task->node_zombie);

    arch_ctx_destroy(task->actx, task->as->arch_vm);
    unwrap_err(as_unbind(task->as, task));
    kmem_cache_free(&task_cache, task);

    return OK;
}

void __noreturn
task_exit(result_t exit_code) {
    task_t* current = unwrap_null(current_task);
    if (current->tid == TID_PM) {
        panic("pm server crashed!");
    }
    
    assert_eq(current->state, T_RUNNING);
    assert_eq(current->listen_on, TID_INVALID);

    pr_trace("task_exit: task tid=%ld name=%s exiting with code %ld",
        current->tid, current->name, exit_code);
    
    current->exit_code = exit_code;
    unwrap_err(notify(pm, NOTIF_TASK_EXIT));
    
    /* ipc clean up */
    if (current->listen_on != TID_INVALID) {
        if (current->listen_on != IPC_OPEN) {
            assert(elem_in_list(&current->node_receiver));
            list_remove(&current->node_receiver);
        }
        pr_warn("task_exit: cleaning up blocked receiver task tid=%ld name=%s",
            current->tid, current->name);
    } else if (elem_in_list(&current->node_sender)) {
        list_remove(&current->node_sender);
        pr_warn("task_exit: cleaning up blocked sender task tid=%ld name=%s",
            current->tid, current->name);
    }
    list_foreach_safe(iter, &current->sender_list, next) {
        task_t* sender = list_entry(
            iter,
            task_t,
            node_sender
        );
        list_remove(&sender->node_sender);
        unwrap_err(notify(sender, NOTIF_IPC_ABORT));
        unwrap_err(task_resume(sender->tid));
        pr_trace("task_exit: aborted sender task tid=%ld name=%s sending to exiting task tid=%ld name=%s",
            sender->tid, sender->name, current->tid, current->name);
    }
    list_foreach_safe(iter, &current->receiver_list, next) {
        task_t* receiver = list_entry(
            iter,
            task_t,
            node_receiver
        );
        list_remove(&receiver->node_receiver);
        unwrap_err(notify(receiver, NOTIF_IPC_ABORT));
        unwrap_err(task_resume(receiver->tid));
        pr_trace("task_exit: aborted receiver task tid=%ld name=%s receiving from exiting task tid=%ld name=%s",
            receiver->tid, receiver->name, current->tid, current->name);
    }

    /* CRITICAL SECTION START */
    current->state = T_ZOMBIE;
    list_remove(&current->node_running);
    list_push_back(&zombie_tasks, &current->node_zombie);
    arch_kctx_switch(
        arch_ctx_kctx(current->actx),
        scheduler_ctx
    );
    unreachable();
}

result_t
task_getzombie(zombie_task_t *out) {
    list_elem_t* elem = list_peak_front(&zombie_tasks);
    if (elem == NULL) {
        return -ERR_NOENT;
    }
    task_t* task = list_entry(elem, task_t, node_zombie);
    out->tid = task->tid;
    out->exit_code = task->exit_code;
    return OK;
}

// called on process context.
// give up cpu and switch to scheduler.
void
task_yield(void) {
    task_t* current = unwrap_null(current_task);
    assert_eq(current->state, T_RUNNING);
    current->state = T_READY;
    /* CRITICAL SECTION START */
    arch_kctx_switch(
        arch_ctx_kctx(current->actx),
        scheduler_ctx
    );
    /* CRITICAL SECTION END */
}

static void
task_dump(void) {
    pr_info("==== task dump start ====");
    list_foreach(iter, &all_tasks) {
        task_t* task = list_entry(iter, task_t, node_all);
        pr_info("task tid=%ld name=%s state=%d",
            task->tid, task->name, task->state);        
    }
    pr_info("==== task dump end ====");
}

void
scheduler(void) {
    pr_info("scheduler started.");

    // currently just simple round-robin
    loop {
        list_foreach_safe(iter, &running_tasks, next) {
            assert(current_task == NULL);
            task_t* task = list_entry(iter, task_t, node_running);
            pr_trace("sched: considering task tid=%ld name=%s state=%d",
                task->tid, task->name, task->state);
            if (task->state == T_READY) {
                task->state = T_RUNNING;

                /* CRITICAL SECTION START */ 
                current_task = task;
                arch_vm_activate(task->as->arch_vm);
                pr_trace("sched: switching to task tid=%ld name=%s",
                    task->tid, task->name);
                arch_kctx_switch(
                    scheduler_ctx,
                    arch_ctx_kctx(task->actx)
                );
                arch_vm_deactivate();
                current_task = NULL;
                /*
                 * CRITICAL SECTION END
                 * Now we are back to scheduler context.
                 */

                assert_ne(task->state, T_RUNNING); // should be managed by various ways
            } else {
                panic("sched: found non-ready task in running_tasks list");
            }
        }

        pr_info("sched: one full round done.");
        pr_info("free pages: %ld", pm_count_free());
        task_dump();
    }
}