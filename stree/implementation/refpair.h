
template<class T, template<class> class CC, class NE>
bool stree::RefPair<T, CC, NE>::implicit() const
{
  return size() > 0;
}


template<class T, template<class> class CC, class NE>
stree::Node<T, CC, NE> * stree::RefPair<T, CC, NE>::next
  (const Context<T> & context) const
{
  int letter = context.text[begin];
  return node->children[letter];
}


template<class T, template<class> class CC, class NE>
bool stree::RefPair<T, CC, NE>::has_trans
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


template<class T, template<class> class CC, class NE>
void stree::RefPair<T, CC, NE>::canonize(const Context<T> & cx)
{
  while(implicit() && next(cx)->size() <= size()){
    node = next(cx);
    begin += node->size();
  } 
}
