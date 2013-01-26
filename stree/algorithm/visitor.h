#ifndef SUFFIX_TREE_VISITOR_H_
#define SUFFIX_TREE_VISITOR_H_

#include <vector>

namespace stree{

class Empty;


template<class T, template<class> class CC, class NE>
class Node;


template<class T, template<class> class CC, class NE>
struct Visit
{
  Node<T, CC, NE> * current;
  int depth;
};


template<class T, template<class> class CC, class NE, class Pp>
struct Visitor
{
  virtual void before(const Visit<T, CC, NE> & visit) {}
  virtual void after(const Visit<T, CC, NE> & visit) {}
  virtual ~Visitor() {}
};

}

#endif
