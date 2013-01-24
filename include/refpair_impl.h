
template<class T>
bool stree::RefPair<T>::implicit() const
{
  return size() > 0;
}


template<class T>
stree::Node<T> * stree::RefPair<T>::next
  (const Context<T> & context) const
{
  int letter = context.text[begin];
  return node->children[letter];
}


template<class T>
bool stree::RefPair<T>::has_trans
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


template<class T>
void stree::RefPair<T>::canonize(const Context<T> & cx)
{
  while(implicit() && next(cx)->size() <= size()){
    node = next(cx);
    begin += node->size();
  } 
}
