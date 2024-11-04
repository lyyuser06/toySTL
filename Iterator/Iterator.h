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
    virtual BaseIterator<Item>& operator++() = 0;
    virtual BaseIterator<Item>& operator--() = 0;
    virtual BaseIterator<Item>& operator++(int) = 0;
    virtual BaseIterator<Item>& operator--(int) = 0;

    /* referance and pointer */
    Item& operator*() const { return *_ptr; }
    Item* operator->() const { return ptr; }

    /* Equal */
    bool operator==(const BaseIterator<Item> &it) const { return (_ptr == it._ptr); }
    bool operator!=(const BaseIterator<Item> &it) const { return !(*this == it); }
};

/*
 * 11.4 
 * 这是一个通用的接口
 * 抽象类类似于Java的接口, 它只为继承类提供一系列统一的接口成员规范.
 * 它只约束了继承类一定要实现这些接口, 并不要求如何实现.
 * 可以仿照Java, 不在抽象类内做任何实质性定义, 只声明
 */ 

#endif