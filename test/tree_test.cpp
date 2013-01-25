#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "suffix_tree.h"


template<class T>
void calculate_pi(const T & begin, const T & end, int * out){
  out[0] = 0;   
  int q = 0;
  for(int i = 1; i < end - begin; i++){
    while(q > 0 && begin[q] != begin[i])
      q = out[q-1];
    if(begin[i] == begin[q])
      q++;
    out[i] = q;
  }
}


// returns (max q, overlap)
template<class PiItr, class RItr> 
std::pair<int, int> find_with_overlap
  (const std::vector<char> & pat, PiItr & pi, RItr begin, RItr end)
{
  unsigned int q = 0;
  unsigned int maxq = 0;
  while(begin != end){
    while(q == pat.size() || (q > 0 && *begin != pat[q]))
      q = pi[q - 1];
    
    if(pat[q] == *begin)
      q++;

    maxq = std::max(maxq, q);
    begin++;
  }

  return std::make_pair(maxq, q);
}



using namespace stree;


TEST(SuffixTree, ContainsAllSubstrings)
{
  const char * text = "bananasandcaca";
  const int len = strlen(text);
  SuffixTree<int> t('z' + 1);

  std::copy(text, text + len, std::back_inserter(t));
  for(const char * begin = text; begin < text + len; begin++){
    for(const char * end = begin + 1; end <= text + len; end++){
      ASSERT_TRUE(t.contains(begin, end));
    }
  }
}


TEST(SuffixTree, BigRandom)
{
  // generate big random text 
  const int size = 1 << 10;
  const int range = 10;
  std::vector<int> text;
  for(int i = 0; i < size; i++)
    text.push_back(rand() % range);

  SuffixTree<int> t(range);   
  std::copy(text.begin(), text.end(), std::back_inserter(t));


  // check some substrings
  const int num_substrings = 1 << 5;
  for(int i = 0; i < num_substrings; i++){
    int begin = rand() % size;
    int end = begin + rand() % (size - begin);
    ASSERT_TRUE(t.contains(text.begin() + begin, text.begin() + end));
  }

  // check some random strings
  const int num_random = 100;
  for(int i = 0; i < num_random; i++){
    const int len = rand() % size;
    std::vector<char> str;
    for(int j = 0; j < len; j++)
      str.push_back(rand() % range);

    // search for this text in
    int * pi = new int[len];
    calculate_pi(str.begin(), str.end(), pi);

    std::pair<int, int> result = find_with_overlap(str, pi, text.begin(), text.end());
    ASSERT_EQ(result.first == len, t.contains(str.begin(), str.end()));

    delete [] pi;
  }
}
