#include <sweetgreen/sweetgreen.h>
#include <stdlib.h>

sweetgreen_test_define(failing_expect_null, positive_comparison_fails) {
  int val, *ptr = &val;
  sweetgreen_expect_null(ptr);
}

sweetgreen_test_define(failing_expect_null, negative_comparison_fails) {
  int *ptr = NULL;
  sweetgreen_expect_not_null(ptr);
}
