#include "task.h"
#include "tns.h"
#include <libs/prelude.h>
#include <libs/elf.h>
#include <libs/iter.h>
#include <uspace/task.h>
#include <uspace/ipc.h>
#include <uspace/syscall.h>

static struct process_t processes[MAX_TASK_NUM];

extern u8 __ustack_bottom[];
extern u8 __ustack_top[];

void
task_init(void) {
    for (usize i = 0; i < MAX_TASK_NUM; i++) {
        processes[i].pid = TID_INVALID;
        processes[i].in_use = false;
        memset(processes[i].path, 0, PATH_MAX_LEN);
        list_init(&processes[i].watchers);
        processes[i].asid = ASID_INVALID;
        processes[i].brk = 0;
    }
}

static result_t
proc_alloc(struct process_t** out_proc) {
    for (usize i = 0; i < MAX_TASK_NUM; i++) {
        if (!processes[i].in_use) {
            processes[i].in_use = true;
            *out_proc = &processes[i];
            assert(list_is_empty(&processes[i].watchers));
            pr_info("process_alloc: allocated process slot %ld", i);
            return OK;
        }
    }
    pr_warn("process_alloc: no free process slot available");
    return -ERR_NOMEM;
}

result_t
proc_get(pid_t pid, struct process_t** out_proc) {
    for (usize i = 0; i < array_size(processes); i++) {
        if (processes[i].pid == pid) {
            assert(processes[i].in_use);
            *out_proc = &processes[i];
            return OK;
        }
    }
    return -ERR_NOENT;
}

static void
proc_free(struct process_t* proc) {
    assert(proc->in_use);
    pr_info("proc_free: freeing process slot %ld pid %ld", 
        proc - processes, proc->pid);
    proc->in_use = false;
    proc->pid = TID_INVALID;
    memset(proc->path, 0, PATH_MAX_LEN);
    proc->asid = ASID_INVALID;
    proc->brk = 0;
} 

result_t
proc_exit(pid_t pid, result_t exit_code) {
    struct process_t* proc = NULL;
    unwrap_err(proc_get(pid, &proc));

    /* resources cleanup goes here. but now empty */
    list_foreach_safe(iter, &proc->watchers, next) {
        struct proc_watcher_t* pw = 
            list_entry(iter, struct proc_watcher_t, node);
        unwrap_err(async_send(
            pw->watcher,
            &(msg_t) {
                .type = MSG_PM,
                .pm = {
                    .type = PM_PROC_EXIT,
                    .proc_exit = {
                        .pid = pid,
                        .xcode = exit_code,
                    }
                }
            }
        ));
        list_remove(&pw->node);
        free(pw);
    }
    tn_cleanup(pid);

    proc_free(proc);
    unwrap_err(sys_task_destroy(pid));
    return OK;
}

static vm_flags_t
pflags2vmflags(usize p_flags) {
    vm_flags_t vm_flags = 0;
    if (p_flags & PF_R) {
        vm_flags |= VM_READ;
    }
    if (p_flags & PF_W) {
        vm_flags |= VM_WRITE;
    }
    if (p_flags & PF_X) {
        vm_flags |= VM_EXEC;
    }
    return vm_flags;
}

/* 
 * length of cmdline cannot exceed SERIAL_BUF_MAX_LEN, 
 * twice to accomodate both argv strings and pointers
 */
static u8 init_stack_buf[SERIAL_BUF_MAX_LEN * 2];

/* System-V ABI without envp & auxv */
static uaddr_t
proc_setup_stack(const cmdline_t* cmdline) {
    extern u8 __ustack_top[];
    
    memset(init_stack_buf, 0, sizeof(init_stack_buf));
    
    u8* buf_top = init_stack_buf + sizeof(init_stack_buf);
    u8* p = buf_top;
    
    uaddr_t argv_ptrs[NUM_CMD_ARGS_MAX];
    
    /* push strings */
    for (isize i = cmdline->argc - 1; i >= 0; i--) {
        usize len = strlen(cmdline->argv[i]) + 1;
        p -= len;
        memcpy(p, cmdline->argv[i], len);
        argv_ptrs[i] = (uaddr_t)__ustack_top - (buf_top - p);
        pr_info("proc_setup_stack: argv[%ld] at 0x%lx: %s",
            i, argv_ptrs[i], (char*)p);
    }
    p = (u8*)align_down((usize)p, sizeof(u64));

    /* push argv pointers */
    p -= sizeof(u64); /* NULL-terminate */
    for (isize i = cmdline->argc - 1; i >= 0; i--) {
        p -= sizeof(u64);
        *((u64*)p) = argv_ptrs[i];
    }
    p -= sizeof(u64); /* argc */
    *((u64*)p) = cmdline->argc;

    /* align to 16 */
    p = (u8*)align_down((usize)p, 16);

    return (uaddr_t)__ustack_top - (buf_top - p);
}

/*
 * it's weird to use cmdline as parameter here
 * in pm server. but it's convenient for message
 * passing, as all information is packed in 
 * a single cmdline string.
 */
result_t
pm_proc_spawn(
    const char* path,
    const u8* elf,
    const cmdline_t* cmdline,
    pid_t* out_pid
) {
    struct process_t* proc = NULL;
    result_t ret = proc_alloc(&proc);
    if (is_err(ret)) {
        goto err;
    }

    elf_hdr_t* elf_hdr = (elf_hdr_t*)elf;
    if (memcmp(elf_hdr->e_ident, ELF_MAGIC, 4) != 0) {
        pr_warn("proc_spawn: invalid elf magic");
        ret = -ERR_INVAL;
        goto err;
    }

    uaddr_t sp = proc_setup_stack(cmdline);
    pid_t pid = sys_task_spawn(
        path,
        elf_hdr->e_entry,
        sp,
        ASID_NEW
    );
    if (is_err(pid)) {
        pr_warn("proc_spawn: sys_task_spawn failed: %s",
            strerr(pid));
        ret = pid;
        goto err;
    }

    asid_t asid = unwrap_err(sys_as_get(pid));
    for (usize i = 0; i < elf_hdr->e_phnum; i++) {
        elf_phdr_t* phdr = (elf_phdr_t*)(elf + 
            elf_hdr->e_phoff + i * sizeof(elf_phdr_t));
        if (phdr->p_type != PT_LOAD) {
            continue;
        }

        vm_flags_t flags = VM_USER | VM_ANON | 
            pflags2vmflags(phdr->p_flags);

        unwrap_err(sys_as_map(
            asid,
            PA2PN(phdr->p_vaddr),
            PPN_ANON,
            PGUP(phdr->p_memsz) / PAGE_SIZE,
            flags
        ));
        if (phdr->p_vaddr != (u64)__ustack_bottom) {
            proc->brk = max(
                proc->brk,
                PA2PN(phdr->p_vaddr + phdr->p_memsz)
            );
        } else {
            /*
             * for stack segment,
             * no need to do following 'memxxx's.
             * but for simplicity we still do them.
             */
        }

        /* write segment data */
        unwrap_err(sys_as_memcpy(
            asid,
            phdr->p_vaddr,
            elf + phdr->p_offset,
            phdr->p_filesz
        ));
        unwrap_err(sys_as_memset(
            asid,
            phdr->p_vaddr + phdr->p_filesz,
            0,
            phdr->p_memsz - phdr->p_filesz
        ));
    }

    /* copy stack content */
    extern u8 __ustack_top[];
    usize copy_size = (uaddr_t)__ustack_top - sp;
    u8* src = init_stack_buf + sizeof(init_stack_buf) - copy_size;
    unwrap_err(sys_as_memcpy(asid, sp, src, copy_size));
    pr_info("proc_spawn: init sp set at 0x%lx, copied %ld bytes",
        sp, copy_size);

    /* map guard page */
    unwrap_err(sys_as_map(
        asid,
        PA2PN((uaddr_t)__ustack_bottom - PAGE_SIZE),
        0,
        1,
        VM_READ | VM_WRITE | VM_FAKE
    ));

    proc->pid = pid;
    strncpy(proc->path, path, PATH_MAX_LEN);
    proc->path[PATH_MAX_LEN - 1] = '\0';   
    proc->asid = asid;
    proc->brk++;
    
    unwrap_err(sys_task_resume(pid));
    *out_pid = pid;
    pr_info("proc_spawn: spawned process '%s' (pid %ld)",
        path, pid);
    return OK;

err:
    if (proc != NULL) {
        proc_free(proc);
    }
    return ret;
}

result_t
pm_proc_watch(pid_t watcher, pid_t target) {
    struct process_t* proc = NULL;
    result_t ret = proc_get(target, &proc);
    if (is_err(ret)) {
        return ret;
    }

    struct proc_watcher_t* pw = 
        (struct proc_watcher_t*)malloc(sizeof(*pw));
    if (pw == NULL) {
        return -ERR_NOMEM;
    }
    pw->watcher = watcher;
    list_push_back(&proc->watchers, &pw->node);
    pr_info("pm_proc_watch: pid %ld watching pid %ld",
        watcher, target);
    return OK;
}

result_t
pm_proc_unwatch(pid_t watcher, pid_t target) {
    struct process_t* proc = NULL;
    result_t ret = proc_get(target, &proc);
    if (is_err(ret)) {
        return ret;
    }

    list_foreach_safe(iter, &proc->watchers, next) {
        struct proc_watcher_t* pw = 
            list_entry(iter, struct proc_watcher_t, node);
        if (pw->watcher == watcher) {
            list_remove(&pw->node);
            free(pw);
            pr_info("pm_proc_unwatch: pid %ld unwatching pid %ld",
                watcher, target);
            return OK;
        }
    }
    return -ERR_NOENT;
}

result_t
vm_map_anon(
    pid_t pid,
    usize npages,
    vpn_t* out
) {
    struct process_t* proc = NULL;
    result_t ret = proc_get(pid, &proc);
    if (is_err(ret)) {
        return ret;
    }

    ret = sys_as_map(
        proc->asid,
        proc->brk,
        PPN_ANON,
        npages,
        VM_USER | VM_ANON | VM_READ | VM_WRITE
    );
    if (is_err(ret)) {
        pr_warn("vm_map_anon: sys_as_map failed: %s",
            strerr(ret));
        return ret;
    }
    *out = proc->brk;
    proc->brk += npages;

    return OK;
}

result_t
vm_map_mmio(
    pid_t pid,
    ppn_t ppn,
    usize npages,
    vpn_t* out
) {
    struct process_t* proc = NULL;
    result_t ret = proc_get(pid, &proc);
    if (is_err(ret)) {
        return ret;
    }

    ret = sys_as_map(
        proc->asid,
        proc->brk,
        ppn,
        npages,
        VM_USER | VM_READ | VM_WRITE
    );
    if (is_err(ret)) {
        pr_warn("vm_map_mmio: sys_as_map failed: %s",
            strerr(ret));
        return ret;
    }
    *out = proc->brk;
    proc->brk += npages;

    return OK;
}

result_t
vm_unmap(
    pid_t pid,
    vpn_t vpn,
    usize npages
) {
    struct process_t* proc = NULL;
    result_t ret = proc_get(pid, &proc);
    if (is_err(ret)) {
        return ret;
    }

    ret = sys_as_unmap(
        proc->asid,
        vpn,
        npages
    );
    if (is_err(ret)) {
        pr_warn("vm_unmap: sys_as_unmap failed: %s",
            strerr(ret));
        return ret;
    }

    return OK;
}
