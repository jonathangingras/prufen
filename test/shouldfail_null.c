#include <prufen/prufen.h>
#include <stdlib.h>

pruf_test_define(failing_expect_null, positive_comparison_fails) {
  int val, *ptr = &val;
  pruf_expect_null(ptr);
}

pruf_test_define(failing_expect_null, negative_comparison_fails) {
  int *ptr = NULL;
  pruf_expect_not_null(ptr);
}
