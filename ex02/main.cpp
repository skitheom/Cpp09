/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 01:51:57 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/10 16:48:13 by sakitaha         ###   ########.fr       */
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
  clock_t end = clock();
  return (static_cast<double>(end - start) / CLOCKS_PER_USEC);
}

template <typename T> void printContainer(const T &t) {
  for (size_t i = 0; i < t.size(); ++i) {
    if (i == 4 && t.size() > 5) {
      std::cout << "[...]\n";
      break;
    }
    std::cout << t[i] << (i < t.size() - 1 ? " " : "\n");
  }
}

template <typename T> bool parseInput(int argc, const char **argv, T &t) {
  for (int i = 1; i < argc; ++i) {
    char *endptr;
    errno = 0;
    long num = std::strtol(argv[i], &endptr, 10);

    if (errno == ERANGE || num > INT_MAX || num < 0 || *endptr != '\0') {
      std::cerr << "Error: Invalid input: " << argv[i] << std::endl;
      return false;
    }
    t.push_back(static_cast<int>(num));
  }
  return true;
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: \"positive integer values to be sorted\"\n";
    return 1;
  }
  std::vector<int> vec;
  std::deque<int> deq;

  if (!parseInput(argc, argv, vec) || !parseInput(argc, argv, deq)) {
    return 1;
  }

  std::cout << "Before (vector): ";
  printContainer(vec);
#ifdef DISPLAY_DEBUG_MSG
  std::cout << "Before (deque): ";
  printContainer(deq);
#endif

  double timeVector = getSortTime(vec);
  double timeDeque = getSortTime(deq);

  std::cout << "After (vector): ";
  printContainer(vec);
#ifdef DISPLAY_DEBUG_MSG
  std::cout << "After (deque): ";
  printContainer(deq);
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
