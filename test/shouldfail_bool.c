#include <prufen/prufen.h>

pruf_test_define(failing_expect_true, positive_comparison_fails) {
  pruf_expect_true(0);
}

pruf_test_define(failing_expect_false, negative_comparison_fails) {
  pruf_expect_false(1);
}
