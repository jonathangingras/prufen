#include <sweetgreen/sweetgreen.h>

sweetgreen_test_define(expect_zero, positive_comparison_works) {
  sweetgreen_expect_zero(0);
}

sweetgreen_test_define(expect_zero, negative_comparison_works) {
  sweetgreen_expect_non_zero(1);
}
