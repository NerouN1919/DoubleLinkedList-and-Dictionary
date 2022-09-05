#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <utility>
#include <string>
#include <iostream>
#include "ForwardList.h"
namespace sviridenko
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using dict_t = Dictionary< Key, Value, Compare >;
    Dictionary();
    Dictionary(const dict_t& other) = default;
    Dictionary(dict_t&& other) = default;
    ~Dictionary() = default;
    dict_t& operator=(const dict_t& other) = default;
    dict_t& operator=(dict_t&& other) = default;
    using iterator_t = typename ForwardList< std::pair< Key, Value > >::Iterator;
    using const_iterator_t = typename ForwardList< std::pair< Key, Value > >::ConstIterator;
    bool isEmpty() const;
    void push(const Key& key, const Value& value);
    Value& operator[](const Key& key);
    bool drop(const Key& key);
    iterator_t begin();
    iterator_t end();
    const_iterator_t cbegin() const;
    const_iterator_t cend() const;
    iterator_t find(const Key& key);
    const_iterator_t constFind(const Key& key) const;
    bool boolFind(const Key& key);
  private:
    Compare cmp;
    sviridenko::ForwardList< std::pair< Key, Value > > list_;
  };
}
template < typename Key, typename Value, typename Compare >
sviridenko::Dictionary< Key, Value, Compare >::Dictionary() : list_()
{}

template < typename Key, typename Value, typename Compare >
bool sviridenko::Dictionary< Key, Value, Compare >::isEmpty() const
{
  return list_.isEmpty();
}

template < typename Key, typename Value, typename Compare >
void sviridenko::Dictionary< Key, Value, Compare >::push(const Key& key, const Value& value)
{
  typename ForwardList< std::pair< Key, Value > >::ConstIterator keyIt = constFind(key);
  if (keyIt != cend())
  {
    return;
  }
  std::pair< Key, Value > tempPair(key, value);
  typename ForwardList< std::pair< Key, Value > >::ConstIterator it = cbegin();
  typename ForwardList< std::pair< Key, Value > >::Iterator prevIt = list_.beforeBegin();
  while (it != cend())
  {
    if (cmp(tempPair.first, it->first))
    {
      list_.insertAfter(prevIt, tempPair);
      return;
    }
    ++it;
    ++prevIt;
  }
  list_.insertAfter(prevIt, tempPair);
  return;
}

template < typename Key, typename Value, typename Compare >
Value& sviridenko::Dictionary< Key, Value, Compare >::operator[](const Key& key)
{
  if (isEmpty())
  {
    throw std::logic_error("dictionary is empty");
  }
  for (iterator_t iter = list_.begin(); iter != list_.end(); iter++)
  {
    if (iter->first == key)
    {
      return iter->second;
    }
  }
  throw std::logic_error("Not such key in dicrionary");
}

template< typename Key, typename Value, typename Compare >
bool sviridenko::Dictionary< Key, Value, Compare >::drop(const Key& key)
{
  typename ForwardList< std::pair< Key, Value > >::ConstIterator it = constFind(key);
  if (it != cend())
  {
    list_.remove(*it);
    return 1;
  }
  return 0;
}

template < typename Key, typename Value, typename Compare >
typename sviridenko::ForwardList< std::pair< Key, Value > >::Iterator sviridenko::Dictionary< Key, Value, Compare >::begin()
{
  iterator_t temp = list_.begin();
  return temp;
}

template < typename Key, typename Value, typename Compare >
typename sviridenko::ForwardList< std::pair< Key, Value > >::Iterator sviridenko::Dictionary< Key, Value, Compare >::end()
{
  iterator_t temp = list_.end();
  return temp;
}

template < typename Key, typename Value, typename Compare >
typename sviridenko::ForwardList< std::pair< Key, Value > >::ConstIterator
sviridenko::Dictionary< Key, Value, Compare >::cbegin() const
{
  const_iterator_t temp = list_.cbegin();
  return temp;
}

template < typename Key, typename Value, typename Compare >
typename sviridenko::ForwardList< std::pair< Key, Value > >::ConstIterator
sviridenko::Dictionary< Key, Value, Compare >::cend() const
{
  const_iterator_t temp = list_.cend();
  return temp;
}

template < typename Key, typename Value, typename Compare >
typename sviridenko::ForwardList< std::pair< Key, Value > >::Iterator
sviridenko::Dictionary< Key, Value, Compare >::find(const Key& key)
{
  iterator_t temp = list_.begin();
  while (temp != list_.end() && temp->first != key)
  {
    temp++;
  }
  return temp;
}

template < typename Key, typename Value, typename Compare >
bool sviridenko::Dictionary< Key, Value, Compare >::boolFind(const Key& key)
{
  iterator_t temp = list_.begin();
  while (temp != list_.end() && temp->first != key)
  {
    iterator_t vanish = temp;
    if (++vanish == list_.end())
    {
      break;
    }
    temp++;
  }
  if (temp != end())
  {
    if (temp->first == key)
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

template < typename Key, typename Value, typename Compare >
typename sviridenko::ForwardList< std::pair< Key, Value > >::ConstIterator
sviridenko::Dictionary< Key, Value, Compare >::constFind(const Key& key) const
{
  const_iterator_t temp = list_.cbegin();
  while (temp != list_.cend() && temp->first != key)
  {
    temp++;
  }
  return temp;
}
#endif
