/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:26:14 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/01 04:30:48 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_HPP
#define LOG_HPP

#include "Utils.hpp"
#include <string>

namespace Log {
void log(const std::string &msg);
void log(const std::string &msg, int value);
void log(const std::string &msg, CmpInt &cmpInt);

template <typename T> void logContainer(const std::string &msg, const T &t) {
#ifdef DISPLAY_DEBUG_MSG
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
#endif
  (void)msg;
  (void)t;
}

template <typename T> void logPairs(const std::string &msg, const T &t) {
#ifdef DISPLAY_DEBUG_MSG
  std::cout << msg;
  for (typename T::const_iterator it = t.begin(); it != t.end(); ++it) {
    std::cout << " (" << it->first << ":" << it->second << ")";
  }
  std::cout << std::endl;
#endif
  (void)msg;
  (void)t;
}
} // namespace Log

#endif // LOG_HPP
