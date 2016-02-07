#include <sweetgreen/sweetgreen.h>

sweetgreen_test_define(expect_equal, positive_comparison_works) {
  sweetgreen_expect_equal(42, 42);
  sweetgreen_expect_equal(0, 0);
}

sweetgreen_test_define(expect_equal, negative_comparison_works) {
  sweetgreen_expect_not_equal(42, 0);
  sweetgreen_expect_not_equal(0, 42);
}
