#include <prufen/prufen.h>

pruf_test_define(segmentation_violation, illegal_call_segfault_is_handled_correctly) {
  int (* uninitialized_function_address)();

  uninitialized_function_address();
}

pruf_test_define(segmentation_violation, illegal_dereference_segfault_is_handled_correctly) {
  int *illegal_address;

  *illegal_address = 0;
}

pruf_test_define(segmentation_violation, SIGSEGV_raised_segfault_is_handled_correctly) {
  raise(SIGSEGV);
}
