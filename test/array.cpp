#include <stree/child_container/array.h>

#include <gtest/gtest.h>

TEST(Array, SoCreative)
{
  stree::Array<int> array(100);

  for(int i = 0; i < 100; i++)
    ASSERT_EQ(0, array[i]);

  ASSERT_EQ(0, array.size());
  ASSERT_EQ(100, array.alphabet_size());

  for(int i = 0; i < 100; i++)
    array[i] = (int*) 1;

  ASSERT_EQ(100, array.size());
}


TEST(Array, IteratorsWork)
{
  typedef stree::Array<int> Arr;
  Arr array(100);
  for(Arr::const_iterator itr = array.begin(); itr != array.end(); itr++){
    ASSERT_FALSE(true);
  }

  for(int i = 0; i < 10; i++){
    array[10 * i] = (int*) 1;
  }
  
  int num = 0;
  for(Arr::const_iterator itr = array.begin(); itr != array.end(); ++itr){
    ASSERT_EQ(num * 10, itr->first);
    ASSERT_EQ((int*) 1, itr->second);
    num++;
  }
}
