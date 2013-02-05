
template<class T, template<class> class CC, class NE>
stree::Node<T, CC, NE>::Node(int b, int e, int s, Type * p) 
  : Substr(b, e), children(s), suffix_link(0), parent(p)
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

  Node<T, CC, NE> * mid = new Node<T, CC, NE>(where.begin, where.end, 
                                              children.alphabet_size(), this);
  children[fl] = mid;
  mid->children[ll] = son;
  son->parent = mid;
  son->begin += where.size();
  return mid;
}

template<class T, template<class> class CC, class NE>
bool stree::Node<T, CC, NE>::leaf() const
{
  return 0 == children.size();
}
