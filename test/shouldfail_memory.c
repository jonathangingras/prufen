#include <sweetgreen/sweetgreen.h>
#include <string.h>
#include <stdlib.h>

const char buffer1[] = "some memory that has to be read";
const char buffer2[] = "some memory that has to be read";
const char not_equal_buffer[] = "some not equal memory that also has to be read";

sweetgreen_test_define(failing_expect_equal_memory, positive_comparison_fails) {
  sweetgreen_expect_equal_memory(buffer1, not_equal_buffer, strlen(buffer1) + 1);
}

sweetgreen_test_define(failing_expect_not_equal_memory, negative_comparison_fails) {
  sweetgreen_expect_not_equal_memory(buffer1, buffer2, strlen(buffer1) + 1);
}

sweetgreen_test_define(failing_expect_equal_memory_on_heap, positive_comparison_fails) {
  char *_buffer1 = malloc(strlen(buffer1) + 1);
  memcpy(_buffer1, buffer1, strlen(buffer1) + 1);
  char *_buffer2 = malloc(strlen(not_equal_buffer) + 1);
  memcpy(_buffer2, not_equal_buffer, strlen(not_equal_buffer) + 1);

  sweetgreen_expect_equal_memory(_buffer1, _buffer2, strlen(_buffer1) + 1);
}

sweetgreen_test_define(failing_expect_not_equal_memory_on_heap, negative_comparison_fails) {
  char *_buffer1 = malloc(strlen(buffer1) + 1);
  memcpy(_buffer1, buffer1, strlen(buffer1) + 1);
  char *_buffer2 = malloc(strlen(buffer2) + 1);
  memcpy(_buffer2, buffer2, strlen(buffer2) + 1);

  sweetgreen_expect_not_equal_memory(_buffer1, _buffer2, strlen(_buffer1) + 1);
}
