/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 01:51:57 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/10 22:54:15 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>

const double CLOCKS_PER_USEC = static_cast<double>(CLOCKS_PER_SEC) / 1000000.0;

template <typename T> double getSortTime(T &t) {
  clock_t start = clock();
  PmergeMe::sort(t);
  return (static_cast<double>(clock() - start) / CLOCKS_PER_USEC);
}

template <typename T> void printContainer(const std::string &msg, const T &t) {
  std::cout << msg;
  for (typename T::iterator it = t.begin(); it != t.end(); ++it) {
    if (it != t.begin()) {
      std::cout << " ";
    }
    std::cout << *it;
  }
  std::cout << std::endl;
}

bool parseInputToVector(int argc, const char **argv, std::vector<int> &vec) {
  vec.reserve(argc - 1);
  for (int i = 1; i < argc; ++i) {
    char *endptr;
    errno = 0;
    long num = std::strtol(argv[i], &endptr, 10);
    if (errno != 0 || num < 0 || num > INT_MAX || *endptr != '\0') {
      std::cerr << "Error: Invalid input: " << argv[i] << std::endl;
      return false;
    }
    vec.push_back(static_cast<int>(num));
  }
  return true;
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: \"positive integer values to be sorted\"\n";
    return 1;
  }
  std::vector<int> vec;
  if (!parseInputToVector(argc, argv, vec)) {
    return 1;
  }
  std::deque<int> deq(vec.begin(), vec.end());

  printContainer("Before (vec):", vec);
#ifdef DISPLAY_DEBUG_MSG
  printContainer("Before (deq):", deq);
#endif

  double timeVector = getSortTime(vec);
  double timeDeque = getSortTime(deq);

  printContainer("After (vec):", vec);
#ifdef DISPLAY_DEBUG_MSG
  printContainer("After (deq):", deq);
#endif

  std::cout << std::fixed << std::setprecision(6);
  std::cout << "Time to process a range of " << vec.size()
            << " elements with std::vector : " << timeVector << " us\n";
  std::cout << "Time to process a range of " << deq.size()
            << " elements with std::deque : " << timeDeque << " us\n";
  return 0;
}

/*
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us
$> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
Before: 141 79 526 321 [...]
After: 79 141 321 526 [...]
Time to process a range of 3000 elements with std::[..] : 62.14389 us
Time to process a range of 3000 elements with std::[..] : 69.27212 us
*/

/*
// 訂正前の内容
template <typename T> void printContainer(const std::string &msg, const T &t) {
  std::cout << msg;
  for (size_t i = 0; i < t.size(); ++i) {
    if (i == 4 && t.size() > 5) {
      std::cout << "[...]\n";
      break;
    }
    std::cout << t[i] << (i < t.size() - 1 ? " " : "\n");
  }
}
*/
