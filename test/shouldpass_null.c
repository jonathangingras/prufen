#include <sweetgreen/sweetgreen.h>
#include <stdlib.h>

sweetgreen_test_define(expect_null, positive_comparison_works) {
  int *ptr = NULL;
  sweetgreen_expect_null(ptr);
}

sweetgreen_test_define(expect_null, negative_comparison_works) {
  int val, *ptr = &val;
  sweetgreen_expect_not_null(ptr);
}
