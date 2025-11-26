#include <libs/prelude.h>
#include <kernel/syscall.h>
#include <kernel/task/sched.h>
#include <kernel/misc/printk.h>

SYSCALL_DEFINE2(
    dbg_puts, 
    const char*, str,
    usize, len
) {
    static char buf[256];
    if (len > array_size(buf) - 1) {
        panic("dbg_puts: len too large %ld", len);
    }
    pr_trace("dbg_puts: str=%p, len=%ld", str, len); 
    memcpy(buf, str, len);
    buf[len] = '\0';

    /* do not use printk to avoid confusion between kernel and user space */
    for (usize i = 0; i < len; i++) {
        arch_dbg_write(buf[i]);
    }
    
    return OK;
}

typedef struct {
    const char* name;
    void (*handler)(void);
} kdb_cmd_t;


void
kdb_ps(void) {
    extern list_t all_tasks;
    printk("NAME\tTID\tSTATE\n");
    list_foreach(iter, &all_tasks) {
        task_t* task = list_entry(iter, task_t, node_all);
        printk("%s\t%ld\t%s\n",
            task->name,
            task->tid,
            task->state == T_READY ? "READY" :
            task->state == T_RUNNING ? "RUNNING" :
            task->state == T_BLOCKED ? "BLOCKED" :
            task->state == T_ZOMBIE ? "ZOMBIE" : "UNKNOWN"
        );
    }
}

void kdb_help(void);
static kdb_cmd_t kdb_cmds[] = {
    { .name = "help", .handler = kdb_help },
    { .name = "ps", .handler = kdb_ps },
};
void
kdb_help(void) {
    printk("kdb: available commands:\n");
    for (usize i = 0; i < array_size(kdb_cmds); i++) {
        printk("  %s\n", kdb_cmds[i].name);
    }
}

SYSCALL_DEFINE1(kdb, const char*, cmd) {
    pr_trace("kdb: cmd=%s", cmd);
    for (usize i = 0; i < array_size(kdb_cmds); i++) {
        if (strcmp(cmd, kdb_cmds[i].name) == 0) {
            kdb_cmds[i].handler();
            return OK;
        }
    }
    pr_warn("kdb: unknown command '%s'", cmd);
    return -ERR_INVAL;
}
