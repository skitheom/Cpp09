#include "RPN.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>

const char *ERR_INVALID_INPUT = "invalid RPN expression";
const char *ERR_EMPTY_STACK = "cannot calculate due to empty stack";
const char *ERR_OVERFLOW = "overflow detected";
const char *ERR_DIV_ZERO = "division by zero";
const char *ERR_INVALID_OP = "invalid operator";

RPN::RPN() {}

RPN::RPN(const RPN &other) { (void)other; }

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &other) {
  if (this != &other) {
  }
  return *this;
}

void RPN::calculateRPN(const std::string &str) {
  if (!isValidInput(str)) {
    throw std::runtime_error(ERR_INVALID_INPUT);
  }

  std::stack<double> stack;
  std::stringstream ss(str);

  for (std::string token; std::getline(ss, token, ' ');) {
    if (token.empty() || token.size() != 1) {
      throw std::runtime_error(ERR_INVALID_INPUT);
    }
    if (isdigit(token[0])) {
      stack.push(token[0] - '0');
      continue;
    }
    double b = prepareValue(stack);
    double a = prepareValue(stack);
    stack.push(basicCalculater(token[0], a, b));
  }
  if (stack.size() != 1) {
    throw std::runtime_error(ERR_INVALID_INPUT);
  }
  std::cout << stack.top() << std::endl;
}

bool RPN::isValidInput(const std::string &str) {
  if (str.empty()) {
    return false;
  }
  bool hasValue = false;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == ' ') {
      continue;
    }
    if (!isdigit(str[i]) && !isOperatorChar(str[i])) {
      return false;
    }
    if (i != str.size() - 1 && str[i + 1] != ' ') {
      return false;
    }
    if (!hasValue) {
      hasValue = true;
    }
  }
  return hasValue;
}

bool RPN::isOperatorChar(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

double RPN::prepareValue(std::stack<double> &stack) {
  if (stack.empty()) {
    throw std::runtime_error(ERR_EMPTY_STACK);
  }
  double value = stack.top();
  stack.pop();
  return value;
}

double RPN::basicCalculater(char token, double a, double b) {

#ifdef DISPLAY_DEBUG_MSG
  std::cerr << "[Debug] Step: " << a << " " << token << " " << b << " = ";
#endif

  double result;
  switch (token) {
  case '+':
    result = a + b;
    break;
  case '-':
    result = a - b;
    break;
  case '*':
    result = a * b;
    break;
  case '/':
    if (b == 0) {
      throw std::runtime_error(ERR_DIV_ZERO);
    }
    result = a / b;
    break;
  default:
    throw std::runtime_error(ERR_INVALID_OP);
  }

#ifdef DISPLAY_DEBUG_MSG
  std::cerr << result << "\n";
#endif
  if (std::isinf(result)) {
    throw std::overflow_error(ERR_OVERFLOW);
  }
  return static_cast<double>(result);
}
