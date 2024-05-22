#ifndef SEQUENCE_OPERATIONS_HPP
#define SEQUENCE_OPERATIONS_HPP

#include <algorithm>
#include <iterator>
#include <forward_list>
#include <iostream>

namespace erohin
{
  template< class T >
  T random(T min, T max)
  {
    return (std::rand() % (max - min) + min);
  }

  template<>
  float random< float >(float min, float max)
  {
    return ((static_cast< float >(std::rand()) / RAND_MAX) * (max - min) + min);
  }

  template< class T, class Container >
  void generate_random(Container & cnt, size_t n)
  {
    std::forward_list< T > seq;
    for (size_t i = 0; i < n; ++i)
    {
      seq.push_front(random< T >(-1000, 1000));
    }
    Container temp(seq.begin(), seq.end());
    cnt.clear();
    cnt = std::move(temp);
  }

  template< class OutputIt >
  void print(std::ostream & output, OutputIt begin, OutputIt end)
  {
    if (begin == end)
    {
      return;
    }
    output << *(begin++);
    while (begin != end)
    {
      output << " " << *(begin++);
    }
  }
}

#endif