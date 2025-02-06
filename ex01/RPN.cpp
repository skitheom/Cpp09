/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:57:32 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/06 20:52:40 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <sstream>

const std::string RPN::ERR_EMPTY_STACK = "cannot calculate due to empty stack";
const std::string RPN::ERR_INVALID_INPUT = "invalid RPN expression";
const std::string RPN::ERR_INVALID_OP = "invalid operator";
const std::string RPN::ERR_OVERFLOW = "overflow detected";
const std::string RPN::ERR_DIV_ZERO = "division by zero";

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

  std::stack<int> stack;
  std::stringstream ss(str);

  for (std::string token; std::getline(ss, token, ' ');) {
    if (token.empty() || token.size() != 1) {
      throw std::runtime_error(ERR_INVALID_INPUT);
    }
    if (isdigit(token[0])) {
      stack.push(token[0] - '0');
      continue;
    }
    int b = prepareValue(stack);
    int a = prepareValue(stack);
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
    hasValue = true;
  }
  return hasValue;
}

bool RPN::isOperatorChar(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::prepareValue(std::stack<int> &stack) {
  if (stack.empty()) {
    throw std::runtime_error(ERR_EMPTY_STACK);
  }
  int value = stack.top();
  stack.pop();
  return value;
}

int RPN::basicCalculater(char token, int a, int b) {

#ifdef DISPLAY_DEBUG_MSG
  std::cerr << "[Debug] Step: " << a << " " << token << " " << b << " = ";
#endif
  long long result;
  switch (token) {
  case '+':
    result = static_cast<long long>(a) + b;
    break;
  case '-':
    result = static_cast<long long>(a) - b;
    break;
  case '*':
    if ((a > 0 && b > 0 && std::numeric_limits<int>::max() / b < a) ||
        (a > 0 && b < 0 && std::numeric_limits<int>::min() / a > b) ||
        (a < 0 && b > 0 && std::numeric_limits<int>::min() / b > a) ||
        (a < 0 && b < 0 && std::numeric_limits<int>::max() / a > b)) {
      throw std::overflow_error(ERR_OVERFLOW);
    }
    result = static_cast<long long>(a) * b;
    break;
  case '/':
    if (b == 0) {
      throw std::runtime_error(ERR_DIV_ZERO);
    }
    result = static_cast<long long>(a) / b;
    break;
  default:
    throw std::runtime_error(ERR_INVALID_OP);
  }

#ifdef DISPLAY_DEBUG_MSG
  std::cerr << result << "\n";
#endif
  if (result > std::numeric_limits<int>::max() ||
      result < std::numeric_limits<int>::min()) {
    throw std::overflow_error(ERR_OVERFLOW);
  }
  return static_cast<int>(result);
}
