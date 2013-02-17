#ifndef STREE_PATH_H_
#define STREE_PATH_H_

#include <stree/algorithm/refpair_visitor.h>

namespace stree
{

template<class T, template<class> class CC, class NE, class II>
void path
  (SuffixTree<T, CC, NE> & tree, 
   RefPairVisitor<T, CC, NE> & visitor,
   II begin, II end)
{
  Node<T, CC, NE> * cur = tree.root();  
  Node<T, CC, NE> * prev;
  int on_edge = 1;
  const std::vector<T> & text = tree.text();
  RefPairVisit<T, CC, NE> visit(
    RefPair<T, CC, NE>(0, 0, 0),
    0
    );

  for(II i = begin; i != end; i++){
    const T & letter = *i;
    if(on_edge == cur->size()){
      if(!cur->children[letter])
        return;
      
      prev = cur;
      cur = cur->children[letter];
      on_edge = 0;
    }
    else{
      unsigned int pos = cur->begin + on_edge;
      if(pos >= text.size() || letter != text[pos])
        return;
    }
    on_edge++;

    visit.depth++;
    visit.current = 
      RefPair<T, CC, NE>(prev, cur->begin, cur->begin + on_edge);
    visitor.before(visit, tree.context());
  }
}

}

#endif
