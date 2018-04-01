#include <prufen/prufen.h>

pruf_test_define(expect_equal, positive_comparison_works) {
  pruf_expect_equal(42, 42);
  pruf_expect_equal(0, 0);
}

pruf_test_define(expect_equal, negative_comparison_works) {
  pruf_expect_not_equal(42, 0);
  pruf_expect_not_equal(0, 42);
}
