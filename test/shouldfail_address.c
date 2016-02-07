#include <sweetgreen/sweetgreen.h>

sweetgreen_test_define(expect_same_addres, positive_comparison_works) {
  int *f, *s;
  sweetgreen_expect_same_address(f, s);
}

sweetgreen_test_define(expect_not_same_address, negative_comparison_works) {
  int *f, *s;
  sweetgreen_expect_not_same_address(f, f);
}
