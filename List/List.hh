#ifndef LIST_H_
#define LIST_H_ 1

#include <iostream>
#include <exception>

/* List Interface */
template <typename Item>
class ListInterface
{
  protected:
    int _size;
  public:
    virtual void insertItem(const Item &item) = 0;
    virtual int size() const { return _size; }
    virtual bool empty() const { return (_size == 0); }
};

/* Single Linked List */
template <typename Item>
class SLList : public ListInterface
{
  protected:
    struct SLListNode
    {
      Item _data;
      SLListNode *_next;
      SLListNode(const Item &data = 0, SLListNode<Item> *next = nullptr) : 
        _data(data), _next(next) {}
    };

    SLListNode<Item> *_header;

    void removeAll()
    {
      SLListNode p = _header;
      while(p != nullptr)
      {
        SLListNode<Item> *pnext = p._next;
        delete p;
        p = pnext;
      }
    }
  public:
    /* Constructors */
    SLList() { _size = 0; _header = new SLListNode(); }
    /* Destructor */
    virtual ~SLList() { removeAll(); }

    /* Interface */
    void insertItem(const Item &item) override { _header._next = new SLListNode(item, _header._next); }
    
};



#endif