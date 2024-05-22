#include <iostream>
#include <stdexcept>
#include <forward_list>
#include <list>
#include <algorithm>
#include "sequence_operations.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc != 4)
  {
    std::cerr << "Wrong CLA's number\n";
    return 1;
  }
  try
  {
    size_t size = std::stoull(argv[3]);
    if (size == 0)
    {
      throw std::invalid_argument("Invalid sequence size");
    }
    std::forward_list< float > random_seq;
    generate_random< float >(random_seq, size);
    random_seq.sort();
    print(std::cout, random_seq.begin(), random_seq.end());
    std::cout << "\n";
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}