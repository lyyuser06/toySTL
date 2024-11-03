#ifndef VECTOR_H_
#define VECTOR_H_

#include "Iterator/Iterator.h"
#define DEFAULT_CAPACITY 3

typedef int ptrdiff;

template <typename Item>
class Vector
{
  protected:
    int _capacity;
    int _size;
    Item *_elem;

    /* This is a tool function that initialize a vector from an item array */
    void copyFromArray(const Item *A, int lo, int hi);
    /* expand and shrink, to keep Vector at a proper capacity */
    void expand();
    void shrink();
    
  public:
    /* Constructors */
    // Vector() = default;
    Vector(int size = 0, const Item &item = 0, int capacity = DEFAULT_CAPACITY);

    Vector(const Item *A, int lo, int hi);
    Vector(const Vector<Item> &vector);
    Vector(Vector<Item> &&vector);

    /* Destructor, only need to free _elem. */
    virtual ~Vector();

    /* ReadOnly Interface */
    int size() const;
    bool empty() const;

    /* Interface */
    Item get(int rank);
    int put(const Item &element, int rank);

    /* Assignment Overload */
    Vector<Item>& operator=(const Vector<Item> &vector);
    Vector<Item>& operator=(Vector<Item> &&vector);

    /* [] overload */
    Item& operator[](int rank);

    /* Insertion */
    void insertItem(int rank, const Item &element);
    void insertItem(const Item &element) { insertItem(_size, element); }

    /* Remove */
    int removeItem(int lo, int hi);
    int removeItem(int rank);

    /* Iterator */
    template <typename T = Item>
    class Iterator : public BaseIterator
    {
      public:
        Iterator(T *ptr) : BaseIterator(ptr) {}
        ~Iterator() {}

        Iterator& operator++() override 
        {
          *_ptr++;
          return *this;
        }
        Iterator& operator--() override 
        {
          *_ptr--;
          return *this;
        }
        Iterator& operator++(int) override { return ++(*this); }
        Iterator& operator--(int) override { return --(*this); }

        /* Random Access Behavior */
        Iterator& operator+=(ptrdiff n)
        {
          _ptr += n;
          return *this;
        }
        Iterator& operator-=(ptrdiff n)
        {
          _ptr -= n;
          return *this;
        }
    }
};

#endif