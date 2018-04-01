#include <prufen/prufen.h>

pruf_test_define(expect_same_addres, positive_comparison_works) {
  int *f, *s;
  pruf_expect_same_address(f, s);
}

pruf_test_define(expect_not_same_address, negative_comparison_works) {
  int *f, *s;
  pruf_expect_not_same_address(f, f);
}
