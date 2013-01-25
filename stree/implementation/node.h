
template<class T>
stree::Node<T>::Node(int b, int e, int s) 
  : Substr(b, e), alphabet_size(s),  suffix_link(0)
{
  children = new stree::Node<T>*[alphabet_size];
  std::fill(children, children + alphabet_size, (Node<T>*)0);
}



template<class T>
stree::Node<T>::~Node()
{
  for(int i = 0; i < alphabet_size; i++)
    delete children[i];

  delete [] children;
}


template<class T>
stree::Node<T> * stree::Node<T>::split
  (const Context<T> & cx, const RefPair<T> & where)
{
  int fl = cx.text[where.begin]; 
  Node<T> * son = children[fl];
  int ll = cx.text[son->begin + where.size()];

  Node<T> * mid = new Node<T>(where.begin, where.end, alphabet_size);
  children[fl] = mid;
  mid->children[ll] = son;
  son->begin += where.size();
  return mid;
}



template<class T>
void stree::Node<T>::dump
  (std::ostream & out, int indent , const Context<T> & cx) const
{ 
  for(int i = 0; i < indent; i++) out << " ";
  
  if(begin == -1){
    out << ":root @ " << this << std::endl;
  }
  else{
    out << "==> ";
    for(int i = begin; i < end && i < cx.text.size(); i++)
      out << (char)(cx.text[i]);

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


template<class T>
bool stree::Node<T>::leaf() const
{
  for(int i = 0; i < alphabet_size; i++)
    if(children[i])
      return false;
  return true;
}
