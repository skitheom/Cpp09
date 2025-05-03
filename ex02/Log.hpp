#ifndef LOG_HPP
#define LOG_HPP

#include "CmpInt.hpp"
#include <iostream>
#include <string>

namespace Log {

template <typename S> void log(const S &msg) {
#ifdef DISPLAY_DEBUG_MSG
  std::cout << msg << std::endl;
#endif
  (void)msg;
}

template <typename S, typename T> void log(const S &msg, const T &value) {
#ifdef DISPLAY_DEBUG_MSG
  std::cout << msg << ": " << value << std::endl;
#endif
  (void)msg;
  (void)value;
}

template <typename T> void logContainer(const std::string &msg, const T &t) {
  size_t count = 0;
#ifdef DISPLAY_DEBUG_MSG
  std::cout << msg << "\t";
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
  std::cout << std::endl;
#endif
  (void)msg;
  (void)t;
  (void)count;
}

} // namespace Log

#endif // LOG_HPP
