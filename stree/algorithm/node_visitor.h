#ifndef SUFFIX_TREE_VISITOR_H_
#define SUFFIX_TREE_VISITOR_H_

#include <vector>

namespace stree{


template<class T, template<class> class CC, class NE>
class Node;

template<class T>
class Context;


/*!
 * Visitor parameters
 */
template<class T, template<class> class CC, class NE>
struct Visit
{
  //! node to process 
  Node<T, CC, NE> * current;

  //! length of uncompressed path from root to current
  int depth;

  /*!
   * @param node node to process
   * @param d depth of node
   */
  Visit(Node<T, CC, NE> * const node, int d)
    : current(node), depth(d) {}
};





/*!
 * Visitor for node traversal (does not process separate characters on
 * edges)
 */
template<class T, template<class> class CC, class NE>
struct NodeVisitor
{

  /*!
   * Gets called before current nodes children are visited
   * @param visit Visit object describing current node
   * @param context tree context
   */
  virtual void before
    (const Visit<T, CC, NE> & visit, const Context<T> & context) 
  {}

  /*!
   * Gets called after current nodes children are visited
   * @param visit Visit object describing current node
   * @param context tree context
   */
  virtual void after
    (const Visit<T, CC, NE> & visit, const Context<T> & context) {}

  virtual ~NodeVisitor() {}
};

}

#endif
