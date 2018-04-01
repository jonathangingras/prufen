#include <prufen/prufen.h>

pruf_test_define(failing_expect_zero, positive_comparison_fails) {
  pruf_expect_zero(1);
}

pruf_test_define(failing_expect_zero, negative_comparison_fails) {
  pruf_expect_non_zero(0);
}
