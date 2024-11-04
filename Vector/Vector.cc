#include "Vector.h"
#include <exception>

template <typename Item>
void Vector<Item>::copyFromArray(const Item *A, int lo, int hi)
{
  if(hi < lo) 
    throw std::runtime_error("Error at Initialization of Array:hi < lo!\n");
  _capacity = 2 * (hi - lo);
  _size = hi - lo;
  _elem = new Item[_capacity];
  for(int i = 0; i < _size; i++)
    _elem[i] = A[lo + i];
}

template <typename Item>
void Vector<Item>::expand()
{
  if(_size < _capacity) return;
  if(_capacity < DEFAULT_CAPACITY) 
    _capacity = DEFAULT_CAPACITY;
  _capacity *= 2;
  Item *oldElem = _elem;
  _elem = new Item[_capacity];
  for(int i = 0; i < _size; i++)
    _elem[i] = oldElem[i];
  delete oldElem;
}

template <typename Item>
void Vector<Item>::shrink()
{
  if(_size > _capacity / 4) return;
  if(_capacity < DEFAULT_CAPACITY) return;
    _capacity /= 2;
  Item *oldElem = _elem;
  _elem = new Item[_capacity];
  for(int i = 0; i < _size; i++)
    elem[i] = oldElem[i];
  delete oldElem;
}

template <typename Item>
Vector<Item>::Vector(int size = 0, const Item &item = 0, int capacity = DEFAULT_CAPACITY) :
  _capacity(capacity), _size(size) 
{
  _elem = new Item[_capacity];
  for(int i = 0; i < _size; i++)
    _elem[i] = item;
}

template <typename Item>
Vector<Item>::Vector(const Item *A, int lo, int hi) { copyFromArray(A, lo, hi); }
template <typename Item>
Vector<Item>::Vector(const Vector<Item> &vector) { copyFromArray(vector._elem, 0, vector._size); }
template <typename Item>
Vector<Item>::Vector(Vector<Item> &&vector)
{
  if(&vector != this)
  {
    _capacity = vector._capacity;
    _size = vector._size;
    _elem = vector._elem;
    vector._elem = nullptr;
  }
}
template <typename Item>
Vector<Item>::~Vector() { delete [] _elem; }
template <typename Item>
int Vector<Item>::size() const { return _size; }
template <typename Item>
bool Vector<Item>::empty() const { return (_size == 0); }
template <typename Item>
Item Vector<Item>::get(int rank) { return _elem[rank]; }
template <typename Item>
int Vector<Item>::put(const Item &element, int rank)
{
  if(rank >= _size) return -1;
    _elem[rank] = element;
  return rank;
} 

template <typename Item>
Vector<Item>& Vector<Item>::operator=(const Vector<Item> &vector)
{
  if(&vector != this)
  {
    if(_elem) delete _elem;
      copyFromArray(vector._elem, 0, vector._size);
  }
  return *this;
}
template <typename Item>
Vector<Item>& Vector<Item>::operator=(Vector<Item> &&vector)
{
  if(&vector != this)
  {
    if(_elem) delete _elem;
    _capacity = vector._capacity;
    _size = vector._size;
    _elem = vector._elem;
    vector._elem = nullptr;
  }
  return *this;
}

template <typename Item>
Item& Vector<Item>::operator[](int rank) { return _elem[rank]; }

template <typename Item>
void Vector<Item>::insertItem(int rank, const Item &element) 
{
  expand();
  for(int i = _size; i > rank; i--)
    _elem[i] = _elem[i - 1];
  _elem[rank] = element;
  _size += 1;
}
template <typename Item>
void Vector<Item>::insertItem(const Item &element) { insertItem(_size, element); }
template <typename Item>
int Vector<Item>::removeItem(int lo, int hi) 
{
  if(hi < lo) 
    throw std::runtime_error("Error at Remove from Array:hi < lo!\n");
  while(hi < _size)
  {
    _elem[lo] = _elem[hi];
    ++lo; ++hi; 
  }
  _size -= (hi - lo);
  return (hi - lo);
}
template <typename Item>
int Vector<Item>::removeItem(int rank) { return removeItem(rank, rank + 1); }

template <typename Item>
Vector<Item>::Iterator<> Vector<Item>::begin() const { return Iterator(_elem); }

Iterator end() const;