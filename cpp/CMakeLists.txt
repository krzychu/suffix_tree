project(suffix_tree)
cmake_minimum_required(VERSION 2.8)

add_library(suffix_tree tree.cpp refpair.cpp node.cpp)

find_package(GTest)

include_directories(${GTEST_INCLUDE_DIR})
add_executable(test components_test.cpp tree_test.cpp)
target_link_libraries(test suffix_tree ${GTEST_BOTH_LIBRARIES})

