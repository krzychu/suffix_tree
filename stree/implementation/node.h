
template<class T, template<class> class CC, class NE>
stree::Node<T, CC, NE>::Node(int b, int e, int s) 
  : Substr(b, e), children(s), alphabet_size(s), suffix_link(0)
{
}



template<class T, template<class> class CC, class NE>
stree::Node<T, CC, NE>::~Node()
{
  children.delete_all();
}


template<class T, template<class> class CC, class NE>
stree::Node<T, CC, NE> * stree::Node<T, CC, NE>::split
  (const Context<T> & cx, const RefPair<T, CC, NE> & where)
{
  int fl = cx.text[where.begin]; 
  Node<T, CC, NE> * son = children[fl];
  int ll = cx.text[son->begin + where.size()];

  Node<T, CC, NE> * mid = new Node<T, CC, NE>(where.begin, where.end, alphabet_size);
  children[fl] = mid;
  mid->children[ll] = son;
  son->begin += where.size();
  return mid;
}



template<class T, template<class> class CC, class NE>
void stree::Node<T, CC, NE>::dump
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


template<class T, template<class> class CC, class NE>
bool stree::Node<T, CC, NE>::leaf() const
{
  return 0 == children.size();
}
