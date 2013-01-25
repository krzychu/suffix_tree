#ifndef SUFFIX_TREE_DFS_H_
#define SUFFIX_TREE_DFS_H_

#include <vector.h>

#include <suffix_tree.h>
#include "visitor.h"

namespace stree{


template<class T, class CC>
struct StackFrame
{
  Node * node;
  bool first_visit;
  int depth;
}


template<class T, class CC>
void dfs(const SuffixTree<T, CC> & tree, Visitor & visitor)
{
  std::vector<>stack;
  stack.push_back(tree.root());

  while(!stack.empty()){
    stack.pop_back();
  }
}

}


#endif
