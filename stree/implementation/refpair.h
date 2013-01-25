
template<class T, class CC>
bool stree::RefPair<T, CC>::implicit() const
{
  return size() > 0;
}


template<class T, class CC>
stree::Node<T, CC> * stree::RefPair<T, CC>::next
  (const Context<T> & context) const
{
  int letter = context.text[begin];
  return node->children[letter];
}


template<class T, class CC>
bool stree::RefPair<T, CC>::has_trans
  (const Context<T> & cx, const T & letter) const
{
  if(implicit()){
    int pos = next(cx)->begin + size();   
    return cx.text[pos] == letter;
  }
  else{
    return node->children[letter];
  }
}


template<class T, class CC>
void stree::RefPair<T, CC>::canonize(const Context<T> & cx)
{
  while(implicit() && next(cx)->size() <= size()){
    node = next(cx);
    begin += node->size();
  } 
}
