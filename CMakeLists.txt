project(suffix_tree)
cmake_minimum_required(VERSION 2.8)

include_directories(stree)

find_package(GTest)
if(${GTEST_FOUND})
  include_directories(${GTEST_INCLUDE_DIR})
  add_executable(test 
    test/components_test.cpp
    test/tree_test.cpp
    test/array.cpp
    test/visitor.cpp
    test/dfs.cpp
    )
  target_link_libraries(test ${GTEST_BOTH_LIBRARIES})
endif()

add_executable( profiling test/profiling.cpp )
add_executable( timing test/profiling.cpp )
add_executable( dump test/dump.cpp )
set_target_properties(profiling PROPERTIES LINK_FLAGS -pg)
