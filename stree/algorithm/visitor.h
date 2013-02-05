#ifndef SUFFIX_TREE_VISITOR_H_
#define SUFFIX_TREE_VISITOR_H_

#include <vector>

namespace stree{


template<class T, template<class> class CC, class NE>
class Node;


template<class T>
class Context;


template<class T, template<class> class CC, class NE>
struct Visit
{
  Node<T, CC, NE> * current;
  int depth;

  Visit(Node<T, CC, NE> * const cur, int d)
    : current(cur), depth(d) {}
};


template<class T, template<class> class CC, class NE>
struct NodeVisitor
{
  virtual void before
    (const Visit<T, CC, NE> &, const Context<T> &) {}

  virtual void after
    (const Visit<T, CC, NE> &, const Context<T> &) {}

  virtual ~NodeVisitor() {}
};

}

#endif
