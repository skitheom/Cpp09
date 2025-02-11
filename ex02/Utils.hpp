/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:34:07 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/11 23:42:20 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "PmergeMe.hpp"
#include <cerrno>
#include <ctime>
#include <iostream>
#include <vector>

class Utils {
public:
  static void parseInput(int argc, const char **argv, std::vector<int> &vec);

  template <typename T> static double getSortTime(T &container) {
    clock_t start = clock();
    PmergeMe::sort(container);
    return (static_cast<double>(clock() - start) / kClocksPerUsec);
  }

  template <typename T>
  static void printContainer(const std::string &msg, const T &container) {
    std::cout << msg;
    for (typename T::const_iterator it = container.begin();
         it != container.end(); ++it) {
      if (it != container.begin()) {
        std::cout << " ";
      }
      std::cout << *it;
    }
    std::cout << std::endl;
  }

private:
  static const double kClocksPerUsec;

  Utils();
  Utils(const Utils &other);
  ~Utils();

  Utils &operator=(const Utils &other);
};

#endif // UTILS_HPP
