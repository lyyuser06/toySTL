#ifndef ITERATOR_H_
#define ITERATOR_H_

/*
 * Base Iterator Class, provide the same Interface for each type of Iterator
*/

template <typename Item>
class BaseIterator
{
  protected:
    Item *_ptr;
  public:
    /* Constructor and Destructor */
    BaseIterator(Item *ptr) : _ptr(ptr) {}
    virtual ~BaseIterator() {}

    /* self change */
    virtual BaseIterator& operator++() = 0;
    virtual BaseIterator& operator--() = 0;
    virtual BaseIterator& operator++(int) = 0;
    virtual BaseIterator& operator--(int) = 0;

    /* referance and pointer */
    Item& operator*() const { return *_ptr; }
    Item* operator->() const { return ptr; }

    /* Equal */
    bool operator==(const BaseIterator &it) { return (_ptr == it._ptr); }
    bool operator!=(const BaseIterator &it) { return !(*this == it); }
};

#endif