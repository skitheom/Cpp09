#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN {
public:
  static void calculateRPN(const std::string &str);

private:
  static bool isOperatorChar(char c);
  static bool isValidInput(const std::string &token);
  static double prepareValue(std::stack<double> &stack);
  static double basicCalculater(char token, double a, double b);

  RPN();
  RPN(const RPN &other);
  ~RPN();

  RPN &operator=(const RPN &other);
};

#endif // RPN_HPP
