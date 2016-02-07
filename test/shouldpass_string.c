#include <sweetgreen/sweetgreen.h>
#include <string.h>
#include <stdlib.h>

const char buffer1[] = "some memory that has to be read";
const char buffer2[] = "some memory that has to be read";
const char not_equal_buffer[] = "some not equal memory that also has to be read";

sweetgreen_test_define(expect_equal_memory, positive_comparison_works) {
  sweetgreen_expect_equal_string(buffer1, buffer2);
}

sweetgreen_test_define(expect_not_equal_string, negative_comparison_works) {
  sweetgreen_expect_not_equal_string(buffer1, not_equal_buffer);
}

sweetgreen_test_define(expect_equal_string_on_heap, positive_comparison_works) {
  char *_buffer1 = malloc(strlen(buffer1) + 1);
  memcpy(_buffer1, buffer1, strlen(buffer1) + 1);
  char *_buffer2 = malloc(strlen(buffer2) + 1);
  memcpy(_buffer2, buffer2, strlen(buffer2) + 1);

  sweetgreen_expect_equal_string(_buffer1, _buffer2);
}

sweetgreen_test_define(expect_not_equal_string_on_heap, negative_comparison_works) {
  char *_buffer1 = malloc(strlen(buffer1) + 1);
  memcpy(_buffer1, buffer1, strlen(buffer1) + 1);
  char *_buffer2 = malloc(strlen(not_equal_buffer) + 1);
  memcpy(_buffer2, not_equal_buffer, strlen(buffer2) + 1);

  sweetgreen_expect_not_equal_string(_buffer1, _buffer2);
}
