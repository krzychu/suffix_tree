#ifndef SUFFIX_TREE_H_
#define SUFFIX_TREE_H_

#include <vector>
#include <iostream>

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

template<class T>
struct RefPair;





template<class T>
struct Node : public Substr
{
  Node<T> ** children;
  int alphabet_size;
  Node<T> * suffix_link;

  Node(int b, int e, int alphabet);
  ~Node();
  
  Node * split(const Context<T> & cx, const RefPair<T> & rp);
  bool leaf() const;

  void dump(std::ostream & out, int indent, const Context<T> & cx) const;
};






template<class T>
struct Context
{
  const std::vector<T> & text;
  Context(const std::vector<T> & t) : text(t) {}
};





template<class T>
struct RefPair : public Substr
{
  Node<T> * node;
  RefPair(Node<T> * n = 0, int b = 0, int e = 0) 
    : Substr(b, e), node(n) {}

  bool implicit() const;
  
  void canonize(const Context<T> & context);
  Node<T> * next(const Context<T> & context) const;
  bool has_trans(const Context<T> & context, const T & letter) const;
};





template<class T>
class SuffixTree
{
  public:

    typedef const T & const_reference; 

    SuffixTree(int alphabet_size);
    ~SuffixTree();
    
    void push_back(const T & letter);

    template<class InputIterator>
    void add(InputIterator begin, InputIterator end);
   
    Node<T> * root() const { return root_; }
    int alphabet_size() const {return alphabet_size_;}

    template<class InputIterator>
    bool contains(InputIterator begin, InputIterator end) const;

    void dump(std::ostream & out) const;

  private:
    Node<T> * aux_;
    Node<T> * root_;
    RefPair<T> active_;

    std::vector<T> text_;
    Context<T> context_;
    int alphabet_size_;
};

}


#include "implementation/refpair.h"
#include "implementation/node.h"
#include "implementation/suffix_tree.h"


#endif
