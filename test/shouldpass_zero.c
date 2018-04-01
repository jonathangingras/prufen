#include <prufen/prufen.h>

pruf_test_define(expect_zero, positive_comparison_works) {
  pruf_expect_zero(0);
}

pruf_test_define(expect_zero, negative_comparison_works) {
  pruf_expect_non_zero(1);
}
