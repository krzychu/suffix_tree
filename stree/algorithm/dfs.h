#ifndef SUFFIX_TREE_DFS_H_
#define SUFFIX_TREE_DFS_H_

#include <vector.h>

#include <suffix_tree.h>
#include "visitor.h"

namespace stree{


template<class T, template<class> class CC, class NE>
struct StackFrame
{
  Node<T, CC, NE> * node;
  bool first_visit;
  int depth;
}


template<class T, template<class> class CC, class NE>
void dfs(const SuffixTree<T, CC, NE> & tree, Visitor<T, CC, NE & visitor)
{
  std::vector<>stack;
  stack.push_back(tree.root());

  while(!stack.empty()){
    stack.pop_back();
  }
}

}


#endif
