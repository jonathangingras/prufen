#include <prufen/prufen.h>
#include <stdlib.h>

pruf_test_define(expect_null, positive_comparison_works) {
  int *ptr = NULL;
  pruf_expect_null(ptr);
}

pruf_test_define(expect_null, negative_comparison_works) {
  int val, *ptr = &val;
  pruf_expect_not_null(ptr);
}
