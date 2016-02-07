#include <sweetgreen/sweetgreen.h>

sweetgreen_test_define(failing_expect_zero, positive_comparison_fails) {
  sweetgreen_expect_zero(1);
}

sweetgreen_test_define(failing_expect_zero, negative_comparison_fails) {
  sweetgreen_expect_non_zero(0);
}
