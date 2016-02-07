#include <sweetgreen/sweetgreen.h>

sweetgreen_test_define(failing_expect_true, positive_comparison_fails) {
  sweetgreen_expect_true(0);
}

sweetgreen_test_define(failing_expect_false, negative_comparison_fails) {
  sweetgreen_expect_false(1);
}
