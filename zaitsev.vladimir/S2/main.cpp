#include <iostream>
#include "stack.hpp"
#include "queue.hpp"

int main()
{
  using namespace zaitsev;
  Queue<int>d;
  Queue<int>d0;
  for (int i = 0; i < 1000; ++i)
    d.push(i);
  Queue<int>d2(d);
  while (!d2.empty())
  {
    std::cout << d2.front()<<'\n';
    d2.pop();
  }
}
