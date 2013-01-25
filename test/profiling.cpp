#include <cstdio>
#include <suffix_tree.h>
#include <cstdlib>

int main()
{
  stree::SuffixTree<int> t(10);
  for(int i = 0; i < 100000; i++)
    t.push_back(rand() % 10);

  return 0;
}
