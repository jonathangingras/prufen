#include <prufen/prufen.h>

pruf_test_define(expect_true, positive_comparison_works) {
  pruf_expect_true(1);
}

pruf_test_define(expect_false, negative_comparison_works) {
  pruf_expect_false(0);
}
