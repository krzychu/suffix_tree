#ifndef SUFFIX_TREE_CHILD_COTTAITR_H_
#define SUFFIX_TREE_CHILD_COTTAITR_H_

#include <algorithm>
#include <functional>
#include <utility>

namespace stree{

template<class T>
class ArrayIterator;



/*
 * Child container that pretends to be ordinary c++ array
 * @param T node type
 */
template<class T>
class Array
{
  public:
    /*!
     * @param alphabet_size size of tree alphabet
     */
    Array(int alphabet_size);
    ~Array();

    int alphabet_size() const { return alphabet_size_; }
    
    T * operator[] (int idx) const 
      { return values_[idx]; }

    T * & operator[] (int idx)
      { return values_[idx]; }

    /*!
     * Deletes all non - NULL pointers
     */
    void delete_all();

    /*!
     * @return number of non - NULL entries
     */
    int size() const;

    friend class ArrayIterator<T>;
    typedef ArrayIterator<T> const_iterator;

    const_iterator begin() const
    {
      const_iterator it(*this, 0, values_[0]);
      it.move();
      return it;
    }

    const_iterator end() const
      {return const_iterator(*this, alphabet_size_, 0) ;}

  private:
    Array(const Array<T> & other);
    void operator = (const Array<T> & other);

    const int alphabet_size_;
    T ** values_;
};




template< class T>
Array<T>::Array(int alphabet_size)
  : alphabet_size_(alphabet_size)
{
  values_ = new T * [alphabet_size];
  std::fill(values_, values_ + alphabet_size, (T*) 0); 
}



template< class T>
Array<T>::~Array()
{
  delete [] values_;
}



template< class T>
void Array<T>::delete_all() 
{
  for(int i = 0; i < alphabet_size_; i++)
    delete values_[i];
}



template< class T>
int Array<T>::size() const
{
  return std::count_if(values_, values_ + alphabet_size_, 
    std::bind1st(std::not_equal_to< T* >(), (T*)0));
}



template< class T>
class ArrayIterator
{
  public:
    ArrayIterator(const Array<T> & array, int pos, T * elem) 
      : array_(array), current_(pos, elem) {}

    typedef std::pair<int, T*> type;
    typedef const std::pair<int, T*> & const_reference;
    typedef const std::pair<int, T*> * const_pointer;

    const_reference operator++();
    type operator++(int);

    const_reference operator* () const
      { return current_; }

    const_pointer operator-> () const
      { return &current_; }

    bool operator == (const ArrayIterator<T> & other) const
      { return other.current_.first == current_.first; }

    bool operator != (const ArrayIterator<T> & other) const
      { return other.current_.first != current_.first; }


    bool valid() const;
    void move();

  private:
    void step();
    const Array<T> & array_;
    std::pair<int, T*> current_; 
};



template<class T>
typename ArrayIterator<T>::type ArrayIterator<T>::operator++(int)
{
  type backup = current_;
  step();
  move();
  return backup;
}


template<class T>
typename ArrayIterator<T>::const_reference 
  ArrayIterator<T>::operator++()
{
  step();
  move();
  return current_;
}

template<class T>
void ArrayIterator<T>::step()
{
  current_.first++;    
  if(valid())
    current_.second = array_[current_.first];
  else
    current_.second = (T*)0;
}


template<class T>
void ArrayIterator<T>::move()
{
  while(valid() && !array_[current_.first])
    step();
}


template<class T>
bool ArrayIterator<T>::valid() const
{
  return current_.first < array_.alphabet_size();
}

};

#endif
