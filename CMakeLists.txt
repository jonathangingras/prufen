cmake_minimum_required(VERSION 3.1)
project(prufen)

#install path (prufen is header only)
install(DIRECTORY include/prufen DESTINATION include)

set(PRUFEN_INCLUDES ./include)
include_directories(${PRUFEN_INCLUDES})

option(BUILD_TESTING "compile tests" OFF)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
