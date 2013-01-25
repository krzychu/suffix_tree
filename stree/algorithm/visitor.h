#ifndef SUFFIX_TREE_VISITOR_H_
#define SUFFIX_TREE_VISITOR_H_

#include <vector>

namespace stree{


template<class T, class CC>
class Node;


template<class T, class CC>
struct Visit
{
  Node<T, CC> * current;
  int depth;
};


template<class T, class CC>
struct Visitor
{
  virtual void before(const Visit<T, CC> & visit) {}
  virtual void after(const Visit<T, CC> & visit) {}
  virtual ~Visitor() {}
};

}

#endif
