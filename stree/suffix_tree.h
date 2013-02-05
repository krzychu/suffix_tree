#ifndef SUFFIX_TREE_H_
#define SUFFIX_TREE_H_

#include <vector>
#include <iostream>

#include <stree/child_container/array.h>

namespace stree{

/*!
 * Placeholder class, where some type is needed
 */
struct Empty {};


/*!
 * Represents substring of a text
 */
struct Substr
{
  //! index of first character of substring
  int begin;

  //! index of character after last character of substring
  int end;

  Substr() {}

  /*!
   * @param b begin value
   * @param e end value
   */
  Substr(int b, int e) : begin(b), end(e) {}

  /*!
   * @return substring size
   */
  int size() const { return end - begin; }
};


template<class T>
struct Context;

template<class T, template<class> class CC, class NE>
struct RefPair;




/*!
 * Tree node
 *
 * @param T tree character type
 * @param CC child container type
 * @param NE node extension type
 */
template<class T, template<class> class CC = Array, class NE = Empty>
struct Node : public Substr
{
  typedef Node<T, CC, NE> Type;

  CC< Node<T, CC, NE> > children;
  Node<T, CC, NE> * suffix_link;
  Node<T, CC, NE> * parent;

  /*!
   * @param b begin index of substring on edge from this node to its parent
   * @param b end index of substring on edge from this node to its parent
   * @param alphabet tree alphabet size
   * @param p pointer to parent node
   */
  Node(int b, int e, int alphabet, Type * p);
  virtual ~Node();
 

  /*!
   * See Ukkonens paper for explanation
   * @param cx current tree context
   * @param rp reference pair of split point
   * @return new node (on path beetween this node and one of its former children)
   */
  Node * split(const Context<T> & cx, const RefPair<T, CC, NE> & rp);

  /*! 
   * Checks if this node is a leaf
   * @return true iff this is a leaf
   */
  bool leaf() const;
};





/*!
 * Context in which node operations should be performed.
 * @param T tree char type
 */
template<class T>
struct Context
{
  const std::vector<T> & text;
  Context(const std::vector<T> & t) : text(t) {}
};




/*!
 * Reference pair, like in Ukkonens paper
 * @param T tree char type
 * @param CC child container
 * @param NE node extension
 */
template<class T, template<class> class CC = Array, class NE = Empty>
struct RefPair : public Substr, public NE
{
  Node<T, CC, NE> * node;
  RefPair(Node<T, CC, NE> * n = 0, int b = 0, int e = 0) 
    : Substr(b, e), node(n) {}

  //! Checks if node is implicit
  bool implicit() const;
 
  //! See Ukkonens paper
  void canonize(const Context<T> & context);

  //! For implicit reference pairs - next node 
  Node<T, CC, NE> * next(const Context<T> & context) const;
  
  /*!
   * Checks if this state has transition labelled with given letter
   * @param context tree context
   * @param letter letter that labels checked transition
   */
  bool has_trans(const Context<T> & context, const T & letter) const;
};




/*!
 * SuffixTree
 *
 * @param T char type
 * @param CC child containter type
 * @param NE node extension type
 */
template<class T, template<class> class CC = Array, class NE = Empty >
class SuffixTree
{
  public:
    typedef const T & const_reference; 
    
    SuffixTree(int alphabet_size);
    ~SuffixTree();
   
    //! Inserts letter to the tree
    void push_back(const T & letter);

    //! Inserts range to the tree
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
