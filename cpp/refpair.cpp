#include "suffix_tree.h"
#include <cassert>
#include <iostream>

using namespace stree;


bool stree::RefPair::implicit() const
{
  return size() > 0;
}


Node * stree::RefPair::next(const Context & context) const
{
  int letter = context.text[begin];
  return node->children[letter];
}


bool stree::RefPair::has_trans(const Context & cx, int letter) const
{
  if(implicit()){
    int pos = next(cx)->begin + size();   
    return cx.text[pos] == letter;
  }
  else{
    return node->children[letter];
  }
}


void stree::RefPair::canonize(const Context & cx)
{
  while(implicit() && next(cx)->size() <= size()){
    node = next(cx);
    begin += node->size();
  } 
}
