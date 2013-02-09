#ifndef SUFFIX_TREE_DUMP_H_
#define SUFFIX_TREE_DUMP_H_

#include <iostream>
#include <algorithm>

#include <stree/algorithm/dfs.h>
#include <stree/algorithm/node_visitor.h>

namespace stree{

template<class T, template<class> class CC, class NE>
class DumpVisitor : public NodeVisitor<T, CC, NE>
{
  public:
    DumpVisitor(std::ostream & out, int step = 2, int shift = 0) 
      : out_(out), indent_(0), indent_step_(step), shift_(shift)
    {}

    virtual void before
      (const NodeVisit<T, CC, NE> & v, const Context<T> & c) 
    {
      for(int i = 0; i < indent_; i++) 
        out_ << " ";

      out_ << "Node : ";
      int end = std::min((int)c.text.size(), (int)v.current->end);
      for(int i = v.current->begin; i < end; i++){
        out_ << (T)(c.text[i] + shift_); 
      }
    
      out_ << "  @" << v.current << std::endl;
      indent_ += indent_step_;
    }

    virtual void after
      (const NodeVisit<T, CC, NE> & v, const Context<T> & c) 
    {
      indent_ -= indent_step_; 
    }
  
  private:
    std::ostream & out_;
    int indent_;
    int indent_step_;
    int shift_;
};



/*!
 * Prints tree content to given stream
 * @param T, CC, NE like in SuffixTree
 * @param tree tree to print
 * @param out stream to write to
 */
template<class T, template<class> class CC, class NE>
void dump(SuffixTree<T, CC, NE> & tree, std::ostream & out)
{
  DumpVisitor<T, CC, NE> visitor(out);
  dfs(tree, visitor);
}

}

#endif
