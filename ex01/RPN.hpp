/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:57:34 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/06 20:04:35 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN {
public:
  static void calculateRPN(const std::string &str);

private:
  static const std::string ERR_EMPTY_STACK;
  static const std::string ERR_INVALID_INPUT;
  static const std::string ERR_INVALID_OP;
  static const std::string ERR_DIV_ZERO;

  static bool isOperatorChar(char c);
  static bool isValidInput(const std::string &token);
  static int prepareValue(std::stack<int> &stack);
  static int basicCalculater(char token, int a, int b);

  RPN();
  RPN(const RPN &other);
  ~RPN();

  RPN &operator=(const RPN &other);
};

#endif // RPN_HPP
