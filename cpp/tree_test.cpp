#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "suffix_tree.h"


using namespace stree;

Text str2text(const char * x, const char * end = 0);

TEST(SuffixTree, ContainsAllSuffixes)
{
  const char * text = "bananasandcaca";
  const int len = strlen(text);
  Tree t(50);

  for(int i = 0; i < len; i++){
    t.add(text[i] - 'a');
   // std::cout << "\n\nnext : " << text[i] << std::endl;;
   // t.dump(std::cout);
  } 

  for(const char * begin = text; begin < text + len; begin++){
    for(const char * end = begin + 1; end <= text + len; end++){
      Text subword = str2text(begin, end);
      /*
      std::cout << "? ";
      for(const char * a = begin; a < end; a++)
        std::cout << *a ;
      std::cout << std::endl;
      */
      ASSERT_TRUE(t.contains(subword));
    }
  }
}
