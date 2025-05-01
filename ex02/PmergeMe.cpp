/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:33:08 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/11 01:0 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "Log.hpp"
#include "PmergeMeDeq.hpp"
#include "PmergeMeVec.hpp"
#include "Print.hpp"
#include "Utils.hpp"
#include <iomanip>

namespace PmergeMe {

void run(int size, const char **userInput) {
  IntVec vec;
  Utils::parseInput(size, userInput, vec);
  IntDeq deq(vec.begin(), vec.end());

  Print::printContainer("Before (vec): ", vec);
  // Log::logContainer("Before (deq): ", deq);

  CmpInt::resetComparisons();
  clock_t vecStart = clock();
  PmergeMeVec::sort(vec);
  clock_t vecEnd = clock();
  int vecCmpCount = CmpInt::getComparisonCount();

  CmpInt::resetComparisons();
  // clock_t deqStart = clock();
  PmergeMeDeq::sort(deq);
  // clock_t deqEnd = clock();
  // int deqComCount = CmpInt::getComparisonCount();

  Print::printContainer("After (vec):  ", vec);
  // Log::logContainer("After (deq):  ", deq);

  std::cout << std::fixed << std::setprecision(1);
  std::cout << "Time to process a range of " << vec.size()
            << " elements with vector : " << Utils::getTime(vecStart, vecEnd)
            << " us, Comparison count: " << vecCmpCount << std::endl;
  // std::cout << "Time to process a range of " << deq.size()
  //           << " elements with deque  : " << Utils::getTime(deqStart, deqEnd)
  //           << " us, Comparison count: " << deqComCount << std::endl;
}

} // namespace PmergeMe
