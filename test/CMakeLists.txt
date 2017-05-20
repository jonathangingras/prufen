
function(add_testcase name)
  add_executable(${name} ${name}.c)
endfunction()

add_testcase(shouldpass_equal)
add_testcase(shouldfail_equal)
add_testcase(shouldpass_zero)
add_testcase(shouldfail_zero)
add_testcase(shouldpass_bool)
add_testcase(shouldfail_bool)
add_testcase(shouldpass_address)
add_testcase(shouldfail_address)
add_testcase(shouldpass_memory)
add_testcase(shouldfail_memory)
add_testcase(shouldpass_string)
add_testcase(shouldfail_string)
add_testcase(shouldpass_null)
add_testcase(shouldfail_null)
add_testcase(shouldfail_segfault)

file(COPY run_tests.bash DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

