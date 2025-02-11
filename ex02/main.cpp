/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 01:51:57 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/12 03:19:13 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "Utils.hpp"
#include <deque>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename T> static double getSortTime(T &container) {

  clock_t start = clock();
  PmergeMe::sort(container);
  clock_t end = clock();
  return (static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC);
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: \"positive integer values to be sorted\"\n";
    return 1;
  }

  try {
    std::vector<int> vec;
    Utils::parseInput(argc, argv, vec);
    std::deque<int> deq(vec.begin(), vec.end());

#ifdef DISPLAY_DEBUG_MSG
    Utils::printContainer("Before (vec): ", vec);
    Utils::printContainer("Before (deq): ", deq);
#else
    Utils::printContainer("Before: ", vec);
#endif

    double timeVector = getSortTime(vec);
    double timeDeque = getSortTime(deq);

#ifdef DISPLAY_DEBUG_MSG
    Utils::printContainer("\nAfter (vec):  ", vec);
    Utils::printContainer("After (deq):  ", deq);
    std::cout << std::fixed << std::setprecision(6);
#else
    Utils::printContainer("After:  ", vec);
#endif

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : " << timeVector << " us\n";
    std::cout << "Time to process a range of " << deq.size()
              << " elements with std::deque  : " << timeDeque << " us\n";
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
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
template <typename T> void Utils::printContainer(const std::string &msg, const T
&t) { std::cout << msg; for (size_t i = 0; i < t.size(); ++i) { if (i == 4 &&
t.size() > 5) { std::cout << "[...]\n"; break;
    }
    std::cout << t[i] << (i < t.size() - 1 ? " " : "\n");
  }
}
*/
