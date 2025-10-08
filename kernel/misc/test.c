/*
 * functions for testing various components
 * of the kernel
 */

#include "kernel/misc/test.h"
#include "kernel/misc/printk.h"
#include "kernel/misc/log.h"
#include "kernel/misc/assert.h"
#include "kernel/mm/pm.h"

void
printk_test(void) {
    printk("------ test printk ------\n");
    printk("1. basic string:\n");
    printk("\the quick brown fox jumps over the lazy dog\n");
    printk("\tlorem ipsum dolor sit amet, consectetur adipiscing elit\n");
    printk("2. integers:\n");
    printk("\ti32-dec: %d, %d, %d\n", 0, -1, 2147483647);
    printk("\ti64-dec: %ld, %ld, %ld\n", 0L, -1L, 9223372036854775807L);
    printk("\tu32-hex: %x, %x, %x\n", 0, 1, 4294967295);
    printk("\tu64-hex: %lx, %lx, %lx\n", 0L, 1L, 18446744073709551615UL);
    printk("\tu32-bin: %b, %b, %b\n", 0, 1, 4294967295);
    printk("\tu64-bin: %lb, %lb, %lb\n", 0L, 1L, 18446744073709551615UL);
    printk("\tu32-ord: %o, %o, %o\n", 0, 1, 4294967295);
    printk("\tu64-ord: %lo, %lo, %lo\n", 0L, 1L, 18446744073709551615UL);
    printk("3. pointer:\n");
    printk("\t%p, %p, %p\n", (void*)0, (void*)-1, (void*)0xFFFFFFFFFFFFFFFF);
    printk("4. char:\n");
    printk("\t%c, %c, %c\n", 'a', 'Z', '0');
    printk("5. mixed:\n");
    printk("\tHello, %s! Your score is %d/%d (0x%x, %b, %o)\n", "Alice", 95, 100, 95, 95, 95);
    printk("6. percent sign: %%\n");
    printk("------ test printk end ------\n");
}

void
panic_test(void) {
    panic("this is a panic test");
    assert(1 == 2);
    assert_eq(1, 2);
    assert_ne(1, 1);
    printk("panic_test: all tests passed (no panic/assert triggered)\n");
}

void
pm_test(void) {
    printk("------ test physical memory allocator ------\n");

    ppn_t pages[10];
    for (int i = 0; i < 10; i++) {
        pages[i] = palloc();
        assert(pages[i] != 0);
        printk("allocated page %d: ppn=%p\n", i, pages[i]);
    }

    for (int i = 0; i < 10; i++) {
        pfree(pages[i]);
        printk("freed page %d: ppn=%p\n", i, pages[i]);
    }

    for (int i = 0; i < 10; i++) {
        ppn_t ppn = palloc();
        assert(ppn != 0);
        printk("re-allocated page %d: ppn=%p\n", i, ppn);
    }

    printk("------ test physical memory allocator end ------\n");
}