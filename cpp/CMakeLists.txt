project(suffix_tree)
cmake_minimum_required(VERSION 2.8)


find_package(GTest)
include_directories(${GTEST_INCLUDE_DIR})
add_executable(test components_test.cpp)
target_link_libraries(test ${GTEST_BOTH_LIBRARIES})

