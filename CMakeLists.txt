cmake_minimum_required(VERSION 3.1)
project(sweetgreen)

#install path (sweetgreen is header only)
install(DIRECTORY include/sweetgreen DESTINATION include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SWEETGREEN_INCLUDES ./include)
include_directories(${SWEETGREEN_INCLUDES})

option(WITH_TESTS "compile tests" OFF)

if(WITH_TESTS)
  add_subdirectory(test)
endif()
