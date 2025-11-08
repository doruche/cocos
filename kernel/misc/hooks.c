/*
 * libgeneric's hooks
 */

#include <libs/hooks.h>
#include <libs/prelude.h>
#include <kernel/misc/printk.h>
#include <kernel/arch/arch.h>
#include <kernel/mm/kmalloc.h>

usize __hook_impl
__puts(const char* str) {
    usize len = 0;
    while (str[len] != '\0') {
        arch_dbg_write(str[len]);
        len++;
    }
    return len;
}

void __noreturn __hook_impl
__panic(const char* msg, ...) {
    va_list ap;
    va_start(ap, msg);
    printk(COLOR_PANIC "[PANIC|%s:%d]\t", __FILE__, __LINE__);
    vprintk(msg, ap);
    printk("\n" COLOR_RESET);
    va_end(ap);
    arch_shutdown();
    __builtin_unreachable();
}

void __noreturn __hook_impl
__panic_no_msg(void) {
    arch_shutdown();
    __builtin_unreachable();
}


usize __hook_impl
__objsize(void* ptr) {
    return kmalloc_objsize(ptr);
}
void* __hook_impl
__malloc(usize size) {
    return kmalloc(size);
}

void __hook_impl
__free(void* ptr) {
    kfree(ptr); 
}