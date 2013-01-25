#ifndef SUFFIX_TREE_CHILD_CONTAINER_H_
#define SUFFIX_TREE_CHILD_CONTAINER_H_

#include <algorithm>
#include <functional>

namespace stree{


template<class T, class CC> 
class Node;


template<class T>
class Array
{
  public:
    Array(int alphabet_size);
    ~Array();

    int alphabet_size() const { return alphabet_size_; }

    Node<T, Array> * operator[] (const T & idx) const 
      { return values_[(int) idx]; }

    Node<T, Array> * & operator[] (const T & idx)
      { return values_[(int) idx]; }

    void delete_all();
    int size() const;

  private:
    Array(const Array<T> & other);
    void operator = (const Array<T> & other);

    const int alphabet_size_;
    Node<T, Array> ** values_;
};




template<class T>
Array<T>::Array(int alphabet_size)
  : alphabet_size_(alphabet_size)
{
  values_ = new Node<T, Array>* [alphabet_size];
  std::fill(values_, values_ + alphabet_size, (Node<T, Array>*) 0); 
}



template<class T>
Array<T>::~Array<T>()
{
  delete [] values_;
}



template<class T>
void Array<T>::delete_all() 
{
  for(int i = 0; i < alphabet_size_; i++)
    delete values_[i];
}



template<class T>
int Array<T>::size() const
{
  return std::count_if(values_, values_ + alphabet_size_, 
    std::bind1st(std::not_equal_to< Node<T, Array>* >(), (Node<T, Array>*)0));
}


};

#endif
