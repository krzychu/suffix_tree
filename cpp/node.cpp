#include "suffix_tree.h"
#include <algorithm>
#include <sstream>

using namespace stree;


stree::Node::Node(int b, int e, int s) 
  : Substr(b, e), alphabet_size(s),  suffix_link(0)
{
  children = new Node*[alphabet_size];
  std::fill(children, children + alphabet_size, (Node*)0);
}


stree::Node::~Node()
{
  for(int i = 0; i < alphabet_size; i++)
    delete children[i];

  delete [] children;
}


Node * stree::Node::split(const Context & cx, const RefPair & where)
{
  int fl = cx.text[where.begin]; 
  Node * son = children[fl];
  int ll = cx.text[son->begin + where.size()];

  Node * mid = new Node(where.begin, where.end, alphabet_size);
  children[fl] = mid;
  mid->children[ll] = son;
  son->begin += where.size();
  return mid;
}



void stree::Node::dump(std::ostream & out, int indent , const Context & cx) const
{ 
  for(int i = 0; i < indent; i++) out << " ";
  
  if(begin == -1){
    out << ":root @ " << this << std::endl;
  }
  else{
    out << "==> ";
    for(int i = begin; i < end && i < cx.text.size(); i++)
      out << (char)(cx.text[i] + 'a');

    if(!leaf())
      out << " " << size();
    else
      out << " leaf";
    out << " " << this << " " << suffix_link;
    out << std::endl;
  }


  for(int i = 0; i < alphabet_size; i++){
    if(children[i]){
      for(int j = 0; j < indent; j++) out << " ";
      out << i << std::endl;
      children[i]->dump(out, indent + 2, cx);
    }
  }
}


bool stree::Node::leaf() const
{
  for(int i = 0; i < alphabet_size; i++)
    if(children[i])
      return false;
  return true;
}
