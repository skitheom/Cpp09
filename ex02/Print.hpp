#ifndef PRINT_HPP
#define PRINT_HPP

#include "CmpInt.hpp"
#include <iostream>
#include <string>

namespace Print {
template <typename T> void printContainer(const std::string &msg, const T &t) {

  std::cout << msg;
  size_t count = 0;
  for (typename T::const_iterator it = t.begin(); it != t.end(); ++it) {
#ifdef MUTE_DEBUG_PRINT
    ++count;
    if (count > 10) {
      std::cout << " [...]\n";
      return;
    }
#endif
    std::cout << " " << *it;
  }
  (void)count;
  std::cout << std::endl;
}

template <typename T> void printMsg(const T &msg) {
  std::cout << msg << std::endl;
}

template <typename T, typename U> void printMsg(const T &msg, const U &value) {
  std::cout << msg << ": " << value << std::endl;
}

template <typename T, typename U, typename V>
void printMsg(const T &msg, const U &value, const V &tail) {
  std::cout << msg << ": " << value << " " << tail << std::endl;
}

template <typename T> void printErrorMsg(const T &msg) {
  std::cerr << msg << std::endl;
}

} // namespace Print

#endif // PRINT_HPP
