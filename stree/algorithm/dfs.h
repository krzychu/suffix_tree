#ifndef SUFFIX_TREE_DFS_H_
#define SUFFIX_TREE_DFS_H_

#include <vector>
#include <iostream>

#include <stree/suffix_tree.h>
#include <stree/algorithm/node_visitor.h>

namespace stree{

/**
 * Stack frame for DFS tree traversal 
 */
template<class T, template<class> class CC, class NE>
struct NodeStackFrame : public NodeVisit<T, CC, NE>
{
  /**
   * Indicates if this is the first time we visit current node
   */
  bool first_visit;

  /**
   * @param node visited node
   * @param depth length of uncompressed path from root to node
   */
  NodeStackFrame(Node<T, CC, NE> * const node, int depth)
    : NodeVisit<T, CC, NE>(node, depth), first_visit(true) {}
};




/**
 * DFS tree traversal
 * @param T, CC, NE like in SuffixTree
 * @param tree tree to traverse
 * @param visitor visitor class to use
 */
template<class T, template<class> class CC, class NE>
void dfs
  (SuffixTree<T, CC, NE> & tree, NodeVisitor<T, CC, NE> & visitor)
{
  typedef NodeStackFrame<T, CC, NE> SF;
  typedef Node<T, CC, NE> N;

  std::vector<SF> stack;
  stack.push_back(SF(tree.root(), 0));

  while(!stack.empty()){
    SF & current = stack.back();

    if(current.first_visit){
      current.first_visit = false;
      visitor.before(current, tree.context()); 
      // iterate all children and put them on stack
      typedef typename CC< Node<T, CC, NE> >::const_iterator itr_t;
      itr_t itr = current.current->children.begin(); 
      itr_t end = current.current->children.end();
      while(itr != end)
      {
        SF cf(itr->second, itr->second->size() + current.depth);
        stack.push_back(cf);
        ++itr;
      }
    }
    else{
      visitor.after(current, tree.context());
      stack.pop_back();
    }
  }
}

}


#endif
