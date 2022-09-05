#ifndef BIDIRECTIONALLIT_LIST
#define BIDIRECTIONALLIT_LIST
#include "Node.h"
#include <cassert>
#include <stdexcept>
namespace sviridenko
{
  template <typename T>
  class BidirectionalList
  {
  private:
    NodeB< T >* head_;
    NodeB< T >* tail_;
    void swap(BidirectionalList& other) noexcept;
    void insertTail(NodeB< T >* x);
    void insertHead(NodeB< T >* x);
    void deleteNodeB(NodeB< T >* x);
    NodeB< T >* searchNodeB(T item);
  public:
    struct IteratorBL
    {
      IteratorBL();
      IteratorBL(const IteratorBL& other);
      ~IteratorBL() = default;
      T& operator*();
      const T& operator*() const;
      IteratorBL& operator=(const IteratorBL& other);
      bool operator!=(const IteratorBL& lhs) const;
      bool operator==(const IteratorBL& lhs) const;
      IteratorBL& operator++();
      IteratorBL operator++(int);
      IteratorBL& operator--();
      IteratorBL operator--(int);
      T* operator->();
      const T* operator->() const;
    private:
      NodeB< T >* current_;
      NodeB< T >* next_;
      NodeB< T >* prev_;
      IteratorBL(NodeB< T >* node, NodeB< T >* prev);
      friend BidirectionalList;
    };
    struct ConstIteratorBL
    {
      ConstIteratorBL();
      ConstIteratorBL(const ConstIteratorBL& other);
      ~ConstIteratorBL() = default;
      const T& operator*() const;
      ConstIteratorBL& operator=(const ConstIteratorBL& other);
      bool operator!=(const ConstIteratorBL& lhs) const;
      bool operator==(const ConstIteratorBL& lhs) const;
      ConstIteratorBL& operator++();
      ConstIteratorBL operator++(int);
      const T* operator->() const;
    private:
      NodeB< T >* current_;
      NodeB< T >* next_;
      NodeB< T >* prev_;
      ConstIteratorBL(NodeB< T >* NodeB);
      friend BidirectionalList;
    };
    ConstIteratorBL cbeforeBegin() const;
    ConstIteratorBL cbegin() const;
    ConstIteratorBL cend() const;
    IteratorBL beforeBegin();
    IteratorBL begin();
    IteratorBL end();
    IteratorBL beforeEnd();
    BidirectionalList();
    BidirectionalList(const BidirectionalList< T >&);
    BidirectionalList(BidirectionalList< T >&&) noexcept;
    ~BidirectionalList();
    BidirectionalList& operator=(const BidirectionalList& right);
    BidirectionalList& operator=(BidirectionalList&& right) noexcept;
    T headItem() const;
    T& headItem();
    T tailItem() const;
    T& tailItem();
    void insertHead(T item);
    void insertTail(T item);
    bool deleteHead();
    bool deleteTail();
    bool deleteItem(const T item);
    bool searchItem(T item);
    bool replaceItem(T itemOld, T itemNew);
    bool isEmpty();
    bool boolSearchItem(T item);
    int counter_;
  };
}

template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL sviridenko::BidirectionalList< T >::beforeEnd()
{
  IteratorBL it = begin();
  NodeB< T >* temp = head_;
  while (temp != nullptr && temp->next_ != nullptr)
  {
    ++it;
    temp = temp->next_;
  }
  return it;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL& sviridenko::BidirectionalList< T >::IteratorBL::operator--()
{
  assert(current_ != nullptr || prev_ != nullptr);
  current_ = prev_;
  if (current_ != nullptr)
  {
    prev_ = current_->prev_;
  }
  else
  {
    prev_ = nullptr;
  }
  return *this;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL sviridenko::BidirectionalList< T >::IteratorBL::operator--(int)
{
  assert(current_ != nullptr || prev_ != nullptr);
  IteratorBL temp(*this);
  --(*this);
  return temp;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL sviridenko::BidirectionalList< T >::cbeforeBegin() const
{
  ConstIteratorBL it;
  it.current_ = nullptr;
  it.next_ = head_;
  return it;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL sviridenko::BidirectionalList< T >::cbegin() const
{
  return ConstIteratorBL(head_);
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL sviridenko::BidirectionalList< T >::cend() const
{
  return ConstIteratorBL(nullptr);
}

template< typename T >
sviridenko::BidirectionalList< T >::ConstIteratorBL::ConstIteratorBL() :
  current_(nullptr),
  next_(nullptr),
  prev_(nullptr)
{}

template< typename T >
sviridenko::BidirectionalList< T >::ConstIteratorBL::ConstIteratorBL(const ConstIteratorBL& other) :
  current_(other.current_),
  next_(other.next_),
  prev_(other.prev_)
{}

template< typename T >
sviridenko::BidirectionalList< T >::ConstIteratorBL::ConstIteratorBL(NodeB< T >* NodeB)
{
  if (NodeB == nullptr)
  {
    current_ = nullptr;
    next_ = nullptr;
    prev_ = nullptr;
  }
  else
  {
    current_ = NodeB;
    next_ = NodeB->next_;
    prev_ = NodeB->prev_;
  }
}

template< typename T >
const T& sviridenko::BidirectionalList< T >::ConstIteratorBL::operator*() const
{
  return current_->data;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL&
sviridenko::BidirectionalList< T >::ConstIteratorBL::operator=(const ConstIteratorBL& other)
{
  ConstIteratorBL newIt(other);
  std::swap(current_, newIt.current_);
  std::swap(next_, newIt.next_);
  std::swap(prev_, newIt.prev_);
  return *this;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::ConstIteratorBL::operator!=(const ConstIteratorBL& lhs) const
{
  return !(*this == lhs);
}

template< typename T >
bool sviridenko::BidirectionalList< T >::ConstIteratorBL::operator==(const ConstIteratorBL& lhs) const
{
  return current_ == lhs.current_;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL& sviridenko::BidirectionalList< T >::ConstIteratorBL::operator++()
{
  current_ = next_;
  if (next_ != nullptr)
  {
    next_ = next_->next_;
  }
  return *this;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL sviridenko::BidirectionalList< T >::ConstIteratorBL::operator++(int)
{
  ConstIteratorBL result(*this);
  ++(*this);
  return result;
}

template< typename T >
T* sviridenko::BidirectionalList< T >::IteratorBL::operator->()
{
  return std::addressof(current_->data);
}

template< typename T >
const T* sviridenko::BidirectionalList< T >::ConstIteratorBL::operator->() const
{
  return std::addressof(current_->data);
}

template< typename T >
bool sviridenko::BidirectionalList< T >::isEmpty()
{
  if (head_ == nullptr)
  {
    return true;
  }
  return false;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL sviridenko::BidirectionalList< T >::beforeBegin()
{
  IteratorBL it;
  it.current_ = nullptr;
  it.next_ = head_;
  return it;
}
template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL sviridenko::BidirectionalList< T >::begin()
{
  return IteratorBL(head_, nullptr);
}
template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL sviridenko::BidirectionalList< T >::end()
{
  return IteratorBL(nullptr, beforeEnd().current_);
}

template< typename T >
sviridenko::BidirectionalList< T >::IteratorBL::IteratorBL() :
  current_(nullptr),
  next_(nullptr)
{}
template< typename T >
sviridenko::BidirectionalList< T >::IteratorBL::IteratorBL(const IteratorBL& other) :
  current_(other.current_),
  next_(other.next_),
  prev_(other.prev_)
{}
template< typename T >
sviridenko::BidirectionalList< T >::IteratorBL::IteratorBL(NodeB< T >* node, NodeB< T >* prev)
{
  this->current_ = node;
  this->prev_ = prev;
}
template< typename T >
T& sviridenko::BidirectionalList< T >::IteratorBL::operator*()
{
  return current_->item_;
}

template< typename T >
const T& sviridenko::BidirectionalList< T >::IteratorBL::operator*() const
{
  return current_->data;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL&
sviridenko::BidirectionalList< T >::IteratorBL::operator=(const IteratorBL& other)
{
  IteratorBL newIt(other);
  std::swap(current_, newIt.current_);
  std::swap(next_, newIt.next_);
  return *this;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::IteratorBL::operator!=(const IteratorBL& lhs) const
{
  return !(*this == lhs);
}

template< typename T >
bool sviridenko::BidirectionalList< T >::IteratorBL::operator==(const IteratorBL& lhs) const
{
  return current_ == lhs.current_;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL& sviridenko::BidirectionalList< T >::IteratorBL::operator++()
{
  assert(this->current_ != nullptr);
  this->prev_ = this->current_;
  this->current_ = this->current_->next_;
  return *this;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL sviridenko::BidirectionalList< T >::IteratorBL::operator++(int)
{
  IteratorBL result(*this);
  ++(*this);
  return result;
}

template< typename T >
const T* sviridenko::BidirectionalList< T >::IteratorBL::operator->() const
{
  return std::addressof(current_->data);
}

template < typename T >
sviridenko::BidirectionalList< T >::BidirectionalList() : head_(nullptr), tail_(nullptr), counter_(0)
{}

template < typename T >
sviridenko::BidirectionalList< T >::BidirectionalList(const BidirectionalList< T >& other) :
  head_(nullptr),
  tail_(nullptr),
  counter_(0)
{
  BidirectionalList< T > temp;
  NodeB< T >* src = other.head_;
  while (src)
  {
    temp.insertTail(src->item_);
    src = src->next_;
  }
  swap(temp);
}

template < typename T >
sviridenko::BidirectionalList< T >::BidirectionalList(BidirectionalList&& other) noexcept : head_(other.head_), tail_(other.tail_),
counter_(other.counter_)
{
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.counter_ = 0;
}

template < typename T >
sviridenko::BidirectionalList< T >::~BidirectionalList()
{
  NodeB< T >* current = nullptr;
  NodeB< T >* next = head_;
  while (next != nullptr)
  {
    current = next;
    next = next->next_;
    delete current;
  }
}


template< typename T >
void sviridenko::BidirectionalList< T >::swap(BidirectionalList& other) noexcept
{
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(counter_, other.counter_);
}

template< typename T >
sviridenko::BidirectionalList< T >& sviridenko::BidirectionalList< T >::operator=(const BidirectionalList& right)
{
  if (this != &right) {
    BidirectionalList temp(right);
    swap(temp);
  }
  return *this;
}

template< typename T >
sviridenko::BidirectionalList< T >& sviridenko::BidirectionalList< T >::operator=(BidirectionalList&& right) noexcept
{
  if (this != &right) {
    swap(right);
  }
  return *this;
}

template< typename T >
void sviridenko::BidirectionalList< T >::insertTail(NodeB< T >* x)
{
  if (tail_ == nullptr)
  {
    head_ = x;
    tail_ = x;
    return;
  }
  x->prev_ = tail_;
  tail_->next_ = x;
  tail_ = x;
}

template< typename T >
void sviridenko::BidirectionalList< T >::insertHead(NodeB< T >* x)
{
  if (head_ == nullptr)
  {
    head_ = x;
    tail_ = x;
    return;
  }
  x->next_ = head_;
  head_ = x;

}

template< typename T >
void sviridenko::BidirectionalList< T >::deleteNodeB(NodeB< T >* x)
{
  if (x->next_ == nullptr && x->prev_ == nullptr)
  {
    tail_ = nullptr;
    head_ = nullptr;
  }
  else if (x->next_ == nullptr)
  {
    x->prev_->next_ = nullptr;
    tail_ = x->prev_;
  }
  else if (x->prev_ == nullptr)
  {
    x->next_->prev_ = nullptr;
    head_ = x->next_;
  }
  else
  {
    x->prev_->next_ = x->next_;
    x->next_->prev_ = x->prev_;
  }
  delete x;

}

template< typename T >
sviridenko::NodeB< T >* sviridenko::BidirectionalList< T >::searchNodeB(T item)
{
  NodeB< T >* x = head_;
  while (x != nullptr && x->item_ != item) {
    x = x->next_;
  }
  return x;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::boolSearchItem(T item)
{
  typename sviridenko::BidirectionalList< T >::IteratorBL temp = begin();
  while (temp != end() && temp.current_->item_ != item)
  {
    typename sviridenko::BidirectionalList< T >::IteratorBL vanish = temp;
    if (++vanish == end())
    {
      break;
    }
    temp++;
  }
  if (temp != end())
  {
    if (temp.current_->item_ == item)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}

template< typename T >
T sviridenko::BidirectionalList< T >::headItem() const
{
  return head_->item_;
}

template< typename T >
T& sviridenko::BidirectionalList< T >::headItem()
{
  return head_->item_;
}

template< typename T >
T sviridenko::BidirectionalList< T >::tailItem() const
{
  if (tail_ != nullptr) {
    return tail_->item_;
  }
  throw ("tailItem - список пуст!");
}

template< typename T >
T& sviridenko::BidirectionalList< T >::tailItem()
{
  if (tail_ != nullptr) {
    return tail_->item_;
  }
  throw ("tailItem - список пуст!");
}

template< typename T >
void sviridenko::BidirectionalList< T >::insertHead(T item)
{
  insertHead(new NodeB< T >(item));
  counter_++;
}

template< typename T >
void sviridenko::BidirectionalList< T >::insertTail(T item)
{
  insertTail(new NodeB< T >(item));
  counter_++;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::deleteHead()
{
  if (head_ == nullptr) {
    return 0;
  }
  deleteNodeB(head_);
  counter_--;
  return 1;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::deleteTail()
{
  if (tail_ == nullptr)
  {
    return 0;
  }
  deleteNodeB(tail_);
  counter_--;
  return 1;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::deleteItem(const T item)
{
  while (boolSearchItem(item))
  {
    deleteNodeB(searchNodeB(item));
    counter_--;
  }
  return 0;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::searchItem(T item)
{
  return (searchNodeB(item) != nullptr);
}

template< typename T >
bool sviridenko::BidirectionalList< T >::replaceItem(T itemOld, T itemNew)
{
  NodeB< T >* x = head_;
  while (boolSearchItem(itemOld))
  {
    searchNodeB(itemOld)->item_ = itemNew;
  }
  x = x->next_;
  return true;
}
#endif
