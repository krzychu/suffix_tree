#ifndef SUFFIX_TREE_CHILD_CONTAINER_H_
#define SUFFIX_TREE_CHILD_CONTAINER_H_

#include <algorithm>
#include <functional>

namespace stree{

template<class Index, class Value>
class Array
{
  public:
    Array(int alphabet_size);
    ~Array();

    int alphabet_size() const { return alphabet_size_; }

    Value * operator[] (const Index & idx) const 
      { return values_[(int) idx]; }

    Value * & operator[] (const Index & idx)
      { return values_[(int) idx]; }

    void delete_all();
    int size() const;

  private:
    Array(const Array<Index, Value> & other);
    void operator = (const Array<Index, Value> & other);

    const int alphabet_size_;
    Value ** values_;
};




template<class Index, class Value>
Array<Index, Value>::Array(int alphabet_size)
  : alphabet_size_(alphabet_size)
{
  values_ = new Value* [alphabet_size];
  std::fill(values_, values_ + alphabet_size, (Value*) 0); 
}



template<class Index, class Value>
Array<Index, Value>::~Array<Index, Value>()
{
  delete [] values_;
}



template<class Index, class Value>
void Array<Index, Value>::delete_all() 
{
  for(int i = 0; i < alphabet_size_; i++)
    delete values_[i];
}



template<class Index, class Value>
int Array<Index, Value>::size() const
{
  return std::count_if(values_, values_ + alphabet_size_, 
    std::bind1st(std::not_equal_to<Value*>(), (Value*)0));
}


};

#endif
