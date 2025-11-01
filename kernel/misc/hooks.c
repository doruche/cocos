/*
 * libgeneric's hooks
 */

#include "libs/hooks.h"
#include "libs/prelude.h"
#include "kernel/misc/printk.h"
#include "libs/log.h"
#include "kernel/arch/sbi.h"
#include "kernel/mm/kmalloc.h"

usize __hook_impl
__puts(const char* str) {
    usize len = 0;
    while (str[len] != '\0') {
        sbi_console_putchar(str[len]);
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
    sbi_shutdown();
    __builtin_unreachable();
}

void __noreturn __hook_impl
__panic_no_msg(void) {
    sbi_shutdown();
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