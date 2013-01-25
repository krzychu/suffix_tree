#include <limits>


template<class T, template<class> class CC, class NE>
stree::SuffixTree<T, CC, NE>::SuffixTree(int alphabet_size)
  : context_(text_), alphabet_size_(alphabet_size)
{
  root_ = new Node<T, CC, NE>(-1, 0, alphabet_size);
  aux_ = new Node<T, CC, NE>(0, 0, alphabet_size);
  for(int i = 0; i < alphabet_size; i++)
    aux_->children[i] = root_;
  root_->suffix_link = aux_;

  active_ = RefPair<T, CC, NE>(root_, 0, 0);
}



template<class T, template<class> class CC, class NE>
stree::SuffixTree<T, CC, NE>::~SuffixTree<T, CC, NE>()
{
  for(int i = 0; i < alphabet_size_; i++)
    aux_->children[i] = 0;
  
  delete aux_;
  delete root_;
}



template<class T, template<class> class CC, class NE>
void stree::SuffixTree<T, CC, NE>::push_back(const T & letter)
{
  const int inf = std::numeric_limits<int>::max() / 4;
  Node<T, CC, NE> * parent;
  Node<T, CC, NE> * last_parent = root_;
  text_.push_back(letter);
  while(!active_.has_trans(context_, letter)){
    parent = active_.node;
    if(active_.implicit())
      parent = parent->split(context_, active_);
   
    // add a leaf
    parent->children[letter] = new Node<T, CC, NE>(active_.end, inf, alphabet_size_);
    
    if(last_parent != root_)
      last_parent->suffix_link = parent;
    last_parent = parent;

    // move active
    active_.node = active_.node->suffix_link;
    active_.canonize(context_);
  }
  
  if(last_parent != root_)
    last_parent->suffix_link = active_.node;

  active_.end++;
  active_.canonize(context_);
}




template<class T, template<class> class CC, class NE>
template<class InputIterator>
bool stree::SuffixTree<T, CC, NE>::contains
  (InputIterator begin, InputIterator end) const
{
  Node<T, CC, NE> * cur = root_;  
  int on_edge = 1;
  for(InputIterator i = begin; i != end; i++){
    const T & letter = *i;
    if(on_edge == cur->size()){
      if(!cur->children[letter])
        return false;
      
      cur = cur->children[letter];
      on_edge = 0;
    }
    else{
      unsigned int pos = cur->begin + on_edge;
      if(pos >= text_.size() || letter != text_[pos])
        return false;
    }
    on_edge++;
  }
  return true;
}



template<class T, template<class> class CC, class NE>
void stree::SuffixTree<T, CC, NE>::dump(std::ostream & out) const
{
  root_->dump(out, 0, context_);
}
