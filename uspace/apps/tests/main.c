#include <libs/prelude.h>
#include <libs/path.h>

result_t
path_test(void) {
    pr_info("path lib test started.");

    char* test_paths[] = {
        "/a/b/c",
        "/a//b///c/",
        "/a/./b/../c",
        "////",
        "/a/b/../../..",
        "/a/b/c/./././d/../e",
        "/a/b/",
        "////a",
        NULL
    };

    char buf[PATH_MAX_LEN];

    for (usize i = 0; test_paths[i] != NULL; i++) {
        path_canonicalize(test_paths[i], buf);
        pr_info("original: '%s' -> canonicalized: '%s'", test_paths[i], buf);
        const char* base = path_basename(buf);
        pr_info("  basename: '%s'", base);
    }

    for (usize i = 0; test_paths[i] != NULL; i++) {
        char parent_buf[PATH_MAX_LEN];
        path_dupparent(test_paths[i], parent_buf);
        pr_info("original: '%s' -> parent: '%s'", test_paths[i], parent_buf);
    }

    pr_info("path lib test completed.");
    return OK;
}

result_t
main(void) {
    path_test();
    return OK;
}
