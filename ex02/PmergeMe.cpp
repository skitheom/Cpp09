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
#include <cstdlib>

/*
この処理は呼び出し側に持たせる方向でいいかもしれん
 if (vec.size() < 2) {
    std::cerr << "Error: not enough elements to be sorted\n";
    std::exit(1);
  }
if (deq.size() < 2) {
    std::cerr << "Error: not enough elements to be sorted\n";
    std::exit(1);
  }
*/

namespace PmergeMe {

void sort(IntVec &unsorted) {

  IntPairVec pairs;
  IntVec sorted;

  pairs.reserve(unsorted.size() / 2);
  sorted.reserve(unsorted.size());

  Log::log("\nSorting vector ...");
  mergeInsertionSort(unsorted, pairs, sorted);
}

void sort(IntDeq &unsorted) {

  IntPairDeq pairs;
  IntDeq sorted;

  Log::log("\nSorting deque ...");
  mergeInsertionSort(unsorted, pairs, sorted);
}
void mergeInsertionSort(IntVec &unsorted, IntPairVec &pairs, IntVec &sorted);
void mergeInsertionSort(U &unsorted, T &pairs, U &sorted) {
#ifdef DISPLAY_DEBUG_MSG
  Utils::printContainer("\tUnsorted container:", unsorted);
#endif
  int singleElement = -1;
  if (unsorted.size() % 2 != 0) {
    singleElement = unsorted.back();
    unsorted.pop_back();
#ifdef DISPLAY_DEBUG_MSG
    std::cout << "\tSingle element handled: " << singleElement << "\n";
#endif
  }
  buildPairs(pairs, unsorted);
#ifdef DISPLAY_DEBUG_MSG
  Utils::printPairs("\tAfter buildPairs:", pairs);
#endif
  mergeSortPairs(pairs, 0, pairs.size() - 1);
#ifdef DISPLAY_DEBUG_MSG
  Utils::printPairs("\tAfter sortPairs: ", pairs);
#endif
  insertJacobsthal(pairs, sorted);
#ifdef DISPLAY_DEBUG_MSG
  Utils::printContainer("\tAfter insertJacobsthal:", sorted);
#endif
  if (singleElement != -1) {
    binaryInsertion(sorted, singleElement);
#ifdef DISPLAY_DEBUG_MSG
    std::cout << "\tAfter inserting \'" << singleElement << "\' ";
    Utils::printContainer(":", sorted);
#endif
  }
  unsorted = sorted;
}

void mergeInsertionSort(IntDeq &unsorted, IntPairDeq &pairs, IntDeq &sorted) {}
} // namespace PmergeMe
