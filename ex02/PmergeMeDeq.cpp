/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeDeq.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:25:58 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/01 04:29:34 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMeDeq.hpp"
#include "Log.hpp"

namespace PmergeMeDeq {

void sort(IntDeq &deq) {

  // IntPairDeq pairs;
  // IntDeq sorted;

  // Log::log("\nSorting deque ...");
  // mergeInsertionSort(unsorted, pairs, sorted);
  (void)deq;
}

// void mergeInsertionSort(IntDeq &unsorted, IntPairDeq &pairs, IntDeq &sorted)
// {
//   Log::logContainer("Unsorted: ", unsorted);

//   int singleElement = -1;
//   if (unsorted.size() % 2 != 0) {
//     singleElement = unsorted.back();
//     unsorted.pop_back();
//     Log::log("Single element: ", singleElement);
//   }

//   buildPairs(pairs, unsorted);
//   Log::logPairs("After buildPairs: ", pairs);

//   mergeSortPairs(pairs, 0, pairs.size() - 1);
//   Log::logPairs("After sortPairs: ", pairs);

//   insertJacobsthal(pairs, sorted);
//   Log::logContainer("After insertJacobsthal: ", sorted);

//   if (singleElement != -1) {
//     binaryInsertion(sorted, singleElement);
//     Log::logContainer("After inserting a single element: ", sorted);
//   }
//   unsorted = sorted;
// }

} // namespace PmergeMeDeq
