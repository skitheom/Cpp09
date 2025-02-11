/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:34:07 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/12 02:03:57 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <cerrno>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

class Utils {
public:
  static void parseInput(int argc, const char **argv, std::vector<int> &vec);

  template <typename T>
  static void printContainer(const std::string &msg, const T &container) {
    std::cout << msg;
    size_t count = 0;
    for (typename T::const_iterator it = container.begin();
         it != container.end(); ++it) {
      std::cout << " " << *it;
#ifdef MUTE_DEBUG_PRINT
      if (++count > 3) {
        std::cout << " [...]";
        break;
      }
#endif
    }
    (void)count;
    std::cout << std::endl;
  }

  template <typename T>
  static void printPairs(const std::string &msg, const T &pairs) {
    std::cout << msg;
    for (typename T::const_iterator it = pairs.begin(); it != pairs.end();
         ++it) {
      std::cout << " (" << it->first << ":" << it->second << ")";
    }
    std::cout << std::endl;
  }

private:
  Utils();
  Utils(const Utils &other);
  ~Utils();

  Utils &operator=(const Utils &other);
};

#endif // UTILS_HPP
