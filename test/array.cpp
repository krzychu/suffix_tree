#include <child_container/array.h>
#include <suffix_tree.h>

#include <gtest/gtest.h>

TEST(Array, SoCreative)
{
  stree::Array<int> array(100);

  for(int i = 0; i < 100; i++)
    ASSERT_EQ(0, array[i]);

  ASSERT_EQ(0, array.size());
  ASSERT_EQ(100, array.alphabet_size());

  for(int i = 0; i < 100; i++)
    array[i] = (stree::Node<int>*) 1;

  ASSERT_EQ(100, array.size());
}
