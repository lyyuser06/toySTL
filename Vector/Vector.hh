#ifndef VECTOR_H_
#define VECTOR_H_ 1

#include <iostream>
#include <exception>
#define DEFAULT_CAPACITY 3

template <typename Item>
class Vector
{
  protected:
    int _capacity;
    int _size;
    Item *_elem;

    /* This is a tool function that initialize a vector from an item array */
    void copyFromArray(const Item *A, int lo, int hi)
    {
      if(hi < lo) 
        throw std::runtime_error("Error at Initialization of Array:hi < lo!\n");
      _capacity = 2 * (hi - lo);
      _size = hi - lo;
      _elem = new Item[_capacity];
      for(int i = 0; i < _size; i++)
        _elem[i] = A[lo + i];
    }

    /* expand and shrink, to keep Vector at a proper capacity */
    void expand()
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

    void shrink()
    {
      if(_size > _capacity / 4) return;
      if(_capacity < DEFAULT_CAPACITY) return;
      _capacity /= 2;
      Item *oldElem = _elem;
      _elem = new Item[_capacity];
      for(int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
      delete oldElem;
    }

  public:
    /* Constructors */
    // Vector() = default;
    Vector(int size = 0, const Item &item = 0, int capacity = DEFAULT_CAPACITY) :
      _capacity(capacity), _size(size) 
    {
      _elem = new Item[_capacity];
      for(int i = 0; i < _size; i++)
        _elem[i] = item;
    }

    Vector(const Item *A, int lo, int hi) { copyFromArray(A, lo, hi); }
    Vector(const Vector<Item> &vector) { copyFromArray(vector._elem, 0, vector._size); }
    Vector(Vector<Item> &&vector)
    {
      if(&vector != this)
      {
        _capacity = vector._capacity;
        _size = vector._size;
        _elem = vector._elem;
        vector._elem = nullptr;
      }
    }

    /* Destructor, only need to free _elem. */
    virtual ~Vector() { delete [] _elem; }

    /* ReadOnly Interface */
    int size() const { return _size; }
    bool empty() const { return (_size == 0); }

    /* Interface */

    /* Assignment Overload */
    Vector<Item>& operator=(const Vector<Item> &vector)
    {
      if(&vector != this)
      {
        if(_elem) delete _elem;
        copyFromArray(vector._elem, 0, vector._size);
      }
      return *this;
    }
    Vector<Item>& operator=(Vector<Item> &&vector)
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

    /* [] overload */
    Item& operator[](int rank) { return _elem[rank]; }

    /* Insertion */
    void insertItem(int rank, const Item &element) 
    {
      expand();
      for(int i = _size; i > rank; i--)
        _elem[i] = _elem[i - 1];
      _elem[rank] = element;
      _size += 1;
    }
    void insertItem(const Item &element) { insertItem(_size, element); }

    /* Remove */
    int removeItem(int lo, int hi) 
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
    int removeItem(int rank) { return removeItem(rank, rank + 1); }
};

#endif