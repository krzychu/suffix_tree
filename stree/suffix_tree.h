#ifndef SUFFIX_TREE_H_
#define SUFFIX_TREE_H_

#include <vector>
#include <iostream>
#include "child_container/array.h"

namespace stree{

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

template<class T, class CC>
struct RefPair;





template<class T, class CC = Array<T> >
struct Node : public Substr
{
  CC children;
  int alphabet_size;
  Node<T, CC> * suffix_link;

  Node(int b, int e, int alphabet);
  ~Node();
  
  Node * split(const Context<T> & cx, const RefPair<T, CC> & rp);
  bool leaf() const;

  void dump(std::ostream & out, int indent, const Context<T> & cx) const;
};






template<class T>
struct Context
{
  const std::vector<T> & text;
  Context(const std::vector<T> & t) : text(t) {}
};





template<class T, class CC = Array<T> >
struct RefPair : public Substr
{
  Node<T, CC> * node;
  RefPair(Node<T, CC> * n = 0, int b = 0, int e = 0) 
    : Substr(b, e), node(n) {}

  bool implicit() const;
  
  void canonize(const Context<T> & context);
  Node<T, CC> * next(const Context<T> & context) const;
  bool has_trans(const Context<T> & context, const T & letter) const;
};





template<class T, class CC = Array<T> >
class SuffixTree
{
  public:

    typedef const T & const_reference; 

    SuffixTree(int alphabet_size);
    ~SuffixTree();
    
    void push_back(const T & letter);

    template<class InputIterator>
    void add(InputIterator begin, InputIterator end);
   
    Node<T, CC> * root() const { return root_; }
    int alphabet_size() const {return alphabet_size_;}

    template<class InputIterator>
    bool contains(InputIterator begin, InputIterator end) const;

    void dump(std::ostream & out) const;

  private:
    Node<T, CC> * aux_;
    Node<T, CC> * root_;
    RefPair<T, CC> active_;

    std::vector<T> text_;
    Context<T> context_;
    int alphabet_size_;
};

}


#include "implementation/refpair.h"
#include "implementation/node.h"
#include "implementation/suffix_tree.h"


#endif
