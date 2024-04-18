#include "topostfix.hpp"

#include <stdexcept>

#include "stack.hpp"
#include "checkdata.hpp"

gladyshev::Queue< std::string > gladyshev::infixToPostfix(Queue< std::string > expression)
{
  Stack< std::string > ops;
  Queue< std::string > output;
  std::string token = "";
  while (!expression.empty())
  {
    std::string value = expression.drop();
    if (isNumber(value))
    {
      output.push(value);
    }
    else if (isOperator(value))
    {
      while (!ops.empty() && isOperator(ops.top()) && checkQuality(ops.top(), value))
      {
        output.push(ops.drop());
      }
      ops.push(value);
    }
    else if (value == "(")
    {
      ops.push(value);
    }
    else if (value == ")")
    {
      while (!ops.empty() && ops.top() != "(")
      {
        output.push(ops.drop());
      }
      ops.drop();
    }
    else
    {
      throw std::logic_error("what is that");
    }
  }
  while (!ops.empty())
  {
    if (ops.top() == "(")
    {
      throw std::logic_error("bad bracket");
    }
    output.push(ops.drop());
  }
  return output;
}
