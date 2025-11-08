/*
 * functions for testing various components
 * of the kernel
 */

#include <kernel/arch/arch.h>
#include <kernel/arch/qemu-virt.h>
#include <libs/prelude.h>
#include <kernel/misc/test.h>
#include <kernel/misc/printk.h>
#include <kernel/mm/pm.h>
#include <kernel/mm/slab.h>

void
printk_test(void) {
    notify("------ test printk ------");
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
    notify("------ test printk end ------");
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
    notify("------ test physical memory allocator ------");

    usize nfree_pages_before = pm_count_free();
    info("nfree pages before test: %d", nfree_pages_before);

    ppn_t pages[10];

    // basic test

    for (int i = 0; i < 10; i++) {
        pages[i] = unwrap_err(pm_alloc());
        printk("allocated page %d: ppn=%p\n", i, pages[i]);
    }

    for (int i = 9; i >= 0; i--) {
        assert(pm_decref(pages[i]));
        printk("freed page %d: ppn=%p\n", i, pages[i]);
    }

    for (int i = 0; i < 10; i++) {
        ppn_t ppn = unwrap_err(pm_alloc());
        printk("re-allocated page %d: ppn=%p\n", i, ppn);
    }

    pm_dump();
    info("nfree pages after allocating multiple pages: %d", pm_count_free());

    for (int i = 0; i < 10; i++) {
        assert(pm_decref(pages[i]));
        printk("freed page %d: ppn=%p\n", i, pages[i]);
    }

    usize nfree_pages_after = pm_count_free();
    assert_eq(nfree_pages_before, nfree_pages_after);
    info("nfree pages after freeing multiple pages: %d", nfree_pages_after);

    pm_dump();

    notify("------ test physical memory allocator end ------");
}

void
slab_test(void) {
    notify("------ test slab allocator ------");

    usize nfree_pages_before = pm_count_free();
    info("nfree pages before test: %d", nfree_pages_before);

    kmem_cache_t cache;
    kmem_cache_create(&cache, "test_cache", 64);
    void* objs[1000];
    for (int i = 0; i < 1000; i++) {
        objs[i] = kmem_cache_alloc(&cache);
        assert(objs[i] != NULL);
        trace("allocated object %d: %p\n", i, objs[i]);
    }
    kmem_cache_dump(&cache);
    for (int i = 0; i < 1000; i++) {
        kmem_cache_free(&cache, objs[i]);
        trace("freed object %d: %p\n", i, objs[i]);
    }
    kmem_cache_dump(&cache);

    usize nfree_pages_after = pm_count_free();
    info("nfree pages after test: %d", nfree_pages_after);

    notify("------ test slab allocator end ------");
}

void
vm_test(void) {
    notify("------ test vm ------");

    usize nfree_pages_before = pm_count_free();
    info("nfree pages before test: %d", nfree_pages_before);

    arch_vm_t* vm = arch_vm_creat();    

    // map some pages
    for (ppn_t ppn = PA2PN(KERN_BASE); ppn < PA2PN(PHYSTOP); ppn++) {
        vpn_t vpn = ppn - PA2PN(KERN_BASE);
        arch_vm_map(
            vm, 
            vpn, 
            ppn, 
            VM_READ | VM_WRITE | VM_EXEC
        );
    }

    info("nfree pages after mapping: %d", pm_count_free());

    // check mappings
    for (vpn_t vpn = 0; vpn < PA2PN(PHYSTOP) - PA2PN(KERN_BASE); vpn++) {
        ppn_t ppn = arch_vm_resolve(vm, vpn);
        assert_eq(ppn, vpn + PA2PN(KERN_BASE));
        arch_vm_unmap(vm, vpn);
    }
    info("nfree pages after unmapping: %d", pm_count_free());
    arch_vm_destroy(vm);

    usize nfree_pages_after = pm_count_free();

    assert_eq(nfree_pages_before, nfree_pages_after);
    info("nfree pages after test: %d", nfree_pages_after);

    notify("------ test pgtbl end ------");
}

void
as_test(void) {
    notify("------ test vm ------");

    usize nfree_pages_before = pm_count_free();
    info("nfree pages before test: %d", nfree_pages_before);

//    vm_space_t test_vms;
//    vm_init(&test_vms);
//
//    // map a region of 10 pages
//    vpn_t test_vpn = 0x0; // some arbitrary address
//    ppn_t pages[10] = {0};
//
//    for (usize i = 0; i < 10; i++) {
//        ppn_t ppn = unwrap_err(pm_alloc());
//        pages[i] = ppn;
//    }    
//    for (usize i = 0; i < 10; i++) {
//        vm_map(
//            &test_vms,
//            test_vpn + i,
//            pages[i],
//            1,
//            VM_READ | VM_WRITE
//        );
//    }
//
//    // identity map kernel space
//    vm_map(
//        &test_vms,
//        PA2PN(KERN_BASE),
//        PA2PN(KERN_BASE),
//        (PHYSTOP - KERN_BASE) / PAGE_SIZE,
//        VM_READ | VM_WRITE | VM_EXEC
//    );
//
//    info("nfree pages after mapping: %d", pm_count_free());
//
//    vm_activate(&test_vms);
//
//    // just write some data to the mapped region
//    // now check the mappings
//    // this should move on without page fault
//
//    for (usize i = 0; i < 10; i++) {
//        volatile u64* ptr = (u64*)PN2PA(test_vpn + i);
//        for (usize j = 0; j < PAGE_SIZE / sizeof(u64); j++) {
//            ptr[j] = (u64)(i + j);
//        }
//    }
//
//    // verify the data from physical memory
//    for (usize i = 0; i < 10; i++) {
//        volatile u64* ptr = (u64*)PN2PA(pages[i]);
//        for (usize j = 0; j < PAGE_SIZE / sizeof(u64); j++) {
//            assert_eq(ptr[j], (u64)(i + j));
//        }
//    }
//    
//
//    // return to no paging mode
//    flush_tlb();
//    extern vm_space_t kernel_vms;
//    vm_activate(&kernel_vms);
//
//    vm_unmap(&test_vms, test_vpn, 10);
//
//    vm_unmap(
//        &test_vms,
//        PA2PN(KERN_BASE),
//        (PHYSTOP - KERN_BASE) / PAGE_SIZE
//    );
//
//    // destroy the vm space
//    vm_destroy(&test_vms);
//    
//    for (usize i = 0; i < 10; i++) {
//        assert(pm_decref(pages[i]));
//    }
//
//    usize nfree_pages_after = pm_count_free();
//    // we use kmem_cache in vm, so the number of free pages may not be the same
//    // but should be close
//    info("nfree pages after test: %d", nfree_pages_after);
//    assert_eq(nfree_pages_before, nfree_pages_after);
//
    notify("------ test vm end ------");
}