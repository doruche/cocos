#include <libs/prelude.h>

static usize __noreturn
fib(usize n) {
    /* test stack overflow */
    return fib(n - 1) + fib(n - 2);
}

result_t
main(void) {
    fib(42);

    unreachable();
}