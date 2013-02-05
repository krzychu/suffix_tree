#ifndef SUFFIX_TREE_H_
#define SUFFIX_TREE_H_

#include <vector>
#include <iostream>
#include "child_container/array.h"

namespace stree{

struct Empty {};

struct Substr
{
  int begin;
  int end;

  Substr() {}
  Substr(int b, int e) : begin(b), end(e) {}
  int size() const { return end - begin; }
};


template<class T>
struct Context;

template<class T, template<class> class CC, class NE>
struct RefPair;





template<class T, template<class> class CC = Array, class NE = Empty>
struct Node : public Substr
{
  typedef Node<T, CC, NE> Type;

  CC< Node<T, CC, NE> > children;
  Node<T, CC, NE> * suffix_link;
  Node<T, CC, NE> * parent;

  Node(int b, int e, int alphabet, Type * p);
  virtual ~Node();
  
  Node * split(const Context<T> & cx, const RefPair<T, CC, NE> & rp);
  bool leaf() const;
};






template<class T>
struct Context
{
  const std::vector<T> & text;
  Context(const std::vector<T> & t) : text(t) {}
};





template<class T, template<class> class CC = Array, class NE = Empty>
struct RefPair : public Substr, public NE
{
  Node<T, CC, NE> * node;
  RefPair(Node<T, CC, NE> * n = 0, int b = 0, int e = 0) 
    : Substr(b, e), node(n) {}

  bool implicit() const;
  
  void canonize(const Context<T> & context);
  Node<T, CC, NE> * next(const Context<T> & context) const;
  bool has_trans(const Context<T> & context, const T & letter) const;
};





template<class T, template<class> class CC = Array, class NE = Empty >
class SuffixTree
{
  public:

    typedef const T & const_reference; 

    SuffixTree(int alphabet_size);
    ~SuffixTree();
    
    void push_back(const T & letter);

    template<class InputIterator>
    void add(InputIterator begin, InputIterator end);
   
    Node<T, CC, NE> * root() const { return root_; }
    int alphabet_size() const {return alphabet_size_;}

    template<class InputIterator>
    bool contains(InputIterator begin, InputIterator end) const;

    Context<T> & context() { return context_; }

  private:
    Node<T, CC, NE> * aux_;
    Node<T, CC, NE> * root_;
    RefPair<T, CC, NE> active_;

    std::vector<T> text_;
    Context<T> context_;
    int alphabet_size_;
};

}


#include "implementation/refpair.h"
#include "implementation/node.h"
#include "implementation/suffix_tree.h"


#endif
