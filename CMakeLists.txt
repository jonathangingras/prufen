cmake_minimum_required(VERSION 3.1)
project(sweetgreen)

#install path (sweetgreen is header only)
install(DIRECTORY include/sweetgreen DESTINATION include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SWEETGREEN_INCLUDES ./include)
include_directories(${SWEETGREEN_INCLUDES})

option(BUILD_TESTING "compile tests" OFF)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
