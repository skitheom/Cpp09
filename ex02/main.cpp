/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 01:51:57 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/01 04:48:18 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>

int main(int argc, const char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: \"positive integer values to be sorted\"\n";
    return 1;
  }

  try {
    PmergeMe::run(argc - 1, argv + 1);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}

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
