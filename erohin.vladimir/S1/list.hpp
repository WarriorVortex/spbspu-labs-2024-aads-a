#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

#include <initializer_list>
#include <stdexcept>
#include "node.hpp"
#include "list_iterator.hpp"
#include "list_const_iterator.hpp"

namespace erohin
{
  template< class T >
  class List
  {
  public:
    using iterator = ListIterator< T >;
    using const_iterator = ListConstIterator< T >;
    List();
    List(const List & list);
    List(List && list) noexcept;
    List(size_t count, const T & value);
    List(std::initializer_list< T > init_list);
    template< class InputIt >
    List(InputIt first, InputIt last);
    ~List();
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    T & front();
    const T & front() const;
    bool empty() const;
    void push_front(const T & value);
    void push_front(T && value);
    void pop_front();
    void clear();
    void swap(List< T > & list);
    iterator insert_after(const_iterator pos, const T & value);
    iterator insert_after(const_iterator pos, T && value);
    iterator insert_after(const_iterator pos, size_t count, const T & value);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    void assign(size_t count, const T & value);
    void assign(std::initializer_list< T > init_list);
    template< class InputIt >
    void assign(InputIt first, InputIt last);
    void splice_after(const_iterator pos, List< T > & other);
    void splice_after(const_iterator pos, List< T > && other);
    void remove(const T & value);
    template< class UnaryPredicate >
    void remove_if(UnaryPredicate p);
    void reverse();
  private:
    Node< T > * head_;
  };

  template< class T >
  List< T >::List():
    head_(nullptr)
  {}

  template< class T >
  List< T >::List(const List< T > & list):
    head_(nullptr)
  {
    auto current_iter = list.begin();
    auto end_iter = list.end();
    while (current_iter != end_iter)
    {
      try
      {
        push_front(*(current_iter++));
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
    reverse();
  }

  template< class T >
  List< T >::List(List< T > && list) noexcept:
    head_(list.head_)
  {
    list.head_ = nullptr;
  }

  template< class T >
  List< T >::List(size_t count, const T & value):
    head_(nullptr)
  {
    for (size_t i = 0; i < count; ++i)
    {
      try
      {
        push_front(value);
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
  }

  template< class T >
  List< T >::List(std::initializer_list< T > init_list):
    head_(nullptr)
  {
    auto init_begin = init_list.begin();
    auto init_end = init_list.end();
    while (init_begin != init_end)
    {
      try
      {
        push_front(*(--init_end));
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
  }

  template< class T >
  template< class InputIt >
  List< T >::List(InputIt first, InputIt last):
    head_(nullptr)
  {
    while(first != last)
    {
      try
      {
        push_front(*(first++));
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
    reverse();
  }

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template< class T >
  ListIterator< T > List< T >::begin()
  {
    return ListIterator< T >(head_);
  }

  template< class T >
  ListIterator< T > List< T >::end()
  {
    return ListIterator< T >(nullptr);
  }

  template< class T >
  ListConstIterator< T > List< T >::begin() const
  {
    return ListConstIterator< T >(head_);
  }

  template< class T >
  ListConstIterator< T > List< T >::end() const
  {
    return ListConstIterator< T >(nullptr);
  }

  template< class T >
  ListConstIterator< T > List< T >::cbegin() const
  {
    return ListConstIterator< T >(head_);
  }


  template< class T >
  ListConstIterator< T > List< T >::cend() const
  {
    return ListConstIterator< T >(nullptr);
  }

  template< class T >
  T & List< T >::front()
  {
    return head_->data_;
  }

  template< class T >
  const T & List< T >::front() const
  {
    return head_->data_;
  }

  template< class T >
  bool List< T >::empty() const
  {
    return !head_;
  }

  template< class T >
  void List< T >::push_front(const T & value)
  {
    Node< T > * elem = new Node< T >(value, head_);
    head_ = elem;
  }

  template< class T >
  void List< T >::push_front(T && value)
  {
    Node< T > * elem = new Node< T >(std::move(value), head_);
    head_ = elem;
  }

  template< class T >
  void List< T >::pop_front()
  {
    Node< T > * new_head = head_->next_;
    delete head_;
    head_ = new_head;
  }

  template< class T >
  void List< T >::clear()
  {
    while (head_)
    {
      pop_front();
    }
  }

  template< class T >
  void List< T >::swap(List< T > & list)
  {
    std::swap(head_, list.head_);
  }

  template< class T >
  ListIterator< T > List< T >::insert_after(ListConstIterator< T > pos, const T & value)
  {
    ListIterator< T > iter_result(pos.node_);
    Node< T > * new_node = new Node< T >(value, iter_result.node_->next_);
    iter_result.node_->next_ = new_node;
    return (++iter_result);
  }

  template< class T >
  ListIterator< T > List< T >::insert_after(ListConstIterator< T > pos, T && value)
  {
    ListIterator< T > iter_result(pos.node_);
    Node< T > * new_node = new Node< T >(std::move(value), iter_result.node_->next_);
    iter_result.node_->next_ = new_node;
    return (++iter_result);
  }

  template< class T >
  ListIterator< T > List< T >::insert_after(ListConstIterator< T > pos, size_t count, const T & value)
  {
    for (size_t i = 0; i < count; ++i)
    {
      pos = insert_after(pos, value);
    }
    return pos;
  }

  template< class T >
  ListIterator< T > List< T >::erase_after(ListConstIterator< T > pos)
  {
    ListIterator< T > iter_result(pos.node_);
    Node< T > * to_delete = iter_result.node_->next_;
    Node< T > * to_become_next = to_delete->next_;
    delete to_delete;
    iter_result.node_->next_ = to_become_next;
    return ListIterator< T >(to_become_next);
  }

  template< class T >
  ListIterator< T > List< T >::erase_after(ListConstIterator< T > first, ListConstIterator< T > last)
  {
    while (first + 1 != last)
    {
      erase_after(first);
    }
    return ListIterator< T >(last.node_);
  }

  template< class T >
  void List< T >::assign(size_t count, const T & value)
  {
    clear();
    for (size_t i = 0; i < count; ++i)
    {
      push_front(value);
    }
  }

  template< class T >
  template< class InputIt >
  void List< T >::assign(InputIt first, InputIt last)
  {
    clear();
    while(first != last)
    {
      try
      {
        push_front(*(first++));
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
    reverse();
  }

  template< class T >
  void List< T >::assign(std::initializer_list< T > init_list)
  {
    clear();
    auto init_begin = init_list.begin();
    auto init_end = init_list.end();
    while (init_begin != init_end)
    {
      try
      {
        push_front(*(--init_end));
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
  }

  template< class T >
  void List< T >::splice_after(ListConstIterator< T > pos, List< T > & other)
  {
    auto iter_current = other.cbegin();
    auto iter_end = other.cend();
    while (iter_current != iter_end)
    {
      insert_after(pos, std::move(*iter_current));
      ++iter_current;
      ++pos;
    }
    other.clear();
  }

  template< class T >
  void List< T >::splice_after(ListConstIterator< T > pos, List< T > && other)
  {
    auto iter_current = other.cbegin();
    auto iter_end = other.cend();
    while (iter_current != iter_end)
    {
      insert_after(pos, std::move(*iter_current));
      ++iter_current;
      ++pos;
    }
    other.clear();
  }

  template< class T >
  void List< T >::remove(const T & value)
  {
    T list_front_value(std::move(front()));
    pop_front();
    if (list_front_value != value)
    {
      push_front(std::move(list_front_value));
    }
    auto iter_begin = cbegin();
    auto iter_end = cend();
    while (iter_begin + 1 != iter_end)
    {
      if (*(iter_begin + 1) == value)
      {
        erase_after(iter_begin);
      }
      else
      {
        ++iter_begin;
      }
    }
  }

  template< class T >
  template< class UnaryPredicate >
  void List< T >::remove_if(UnaryPredicate p)
  {
    T list_front_value(std::move(front()));
    pop_front();
    if (!p(list_front_value))
    {
      push_front(std::move(list_front_value));
    }
    auto iter_begin = cbegin();
    auto iter_end = cend();
    while (iter_begin + 1 != iter_end)
    {
      if (p(*(iter_begin + 1)))
      {
        erase_after(iter_begin);
      }
      else
      {
        ++iter_begin;
      }
    }
  }

  template< class T >
  void List< T >::reverse()
  {
    ListConstIterator< T > iter_begin = cbegin();
    ListConstIterator< T > iter_end = cend();
    ListConstIterator< T > iter_current = iter_begin;
    if (iter_current == iter_end)
    {
      return;
    }
    ++iter_current;
    while(iter_current != iter_end)
    {
      push_front(std::move(iter_current.node_->data_));
      ++iter_current;
    }
    erase_after(iter_begin, iter_end);
  }
}

#endif