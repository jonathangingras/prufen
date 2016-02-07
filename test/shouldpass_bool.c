#include <sweetgreen/sweetgreen.h>

sweetgreen_test_define(expect_true, positive_comparison_works) {
  sweetgreen_expect_true(1);
}

sweetgreen_test_define(expect_false, negative_comparison_works) {
  sweetgreen_expect_false(0);
}
