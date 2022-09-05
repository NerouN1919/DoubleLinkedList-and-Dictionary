#ifndef NODE
#define NODE
namespace sviridenko
{
  template <typename T>
  struct NodeB
  {
    T item_;
    NodeB< T >* next_;
    NodeB< T >* prev_;
    explicit NodeB< T >(const T& item, NodeB< T >* next = nullptr, NodeB< T >* prev = nullptr) : item_(item), next_(next), prev_(prev)
    {}
  };
}
#endif
