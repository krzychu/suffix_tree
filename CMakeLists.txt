project(suffix_tree)
cmake_minimum_required(VERSION 2.8)

include_directories(include)

find_package(GTest)
if(${GTEST_FOUND})
  include_directories(${GTEST_INCLUDE_DIR})
  add_executable(test test/components_test.cpp)
  target_link_libraries(test ${GTEST_BOTH_LIBRARIES})
endif()
