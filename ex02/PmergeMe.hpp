/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:48:53 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/11 23:39:42 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <deque>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

class PmergeMe {
public:
  static void sort(std::vector<int> &vec);
  static void sort(std::deque<int> &deq);

private:
  PmergeMe();
  PmergeMe(const PmergeMe &other);
  ~PmergeMe();

  PmergeMe &operator=(const PmergeMe &other);

  static void xreserve(std::vector<std::pair<int, int> > &pairs, size_t size);
  static void xreserve(std::deque<std::pair<int, int> > &pairs, size_t size);

  /**
   * Step 1: Build pairs from the unsorted container.
   **/
  template <typename T, typename U>
  static void buildPairs(T &pairs, const U &unsorted) {
    if (unsorted.size() % 2 != 0) {
      throw std::runtime_error("Error: Number of elements must be even");
    }
    for (typename U::const_iterator it = unsorted.begin(); it != unsorted.end();
         ++it) {
      int a = *it;
      ++it;
      if (it == unsorted.end()) {
        throw std::runtime_error("Error: Unexpected end before making pair");
      }
      int b = *it;
      if (a < b) {
        std::swap(a, b);
      }
      pairs.push_back(std::make_pair(a, b));
    }
  };

  /**
   * Step 2: Perform merge sort on pairs based on the values of the leaders.
   */
  template <typename T>
  static void mergeSortPairs(T &pairs, size_t left, size_t right) {
    if (left >= right) {
      return;
    }
    size_t mid = left + (right - left) / 2;
    mergeSortPairs(pairs, left, mid);
    mergeSortPairs(pairs, mid + 1, right);
    mergePairs(pairs, left, mid, right);
  }

  template <typename T>
  static void mergePairs(T &pairs, size_t left, size_t mid, size_t right) {
    size_t sizeLeft = mid - left + 1;
    size_t sizeRight = right - mid;
    T leftPairs;
    T rightPairs;

    xreserve(leftPairs, sizeLeft);
    xreserve(rightPairs, sizeRight);
    for (size_t i = 0; i < sizeLeft; ++i) {
      leftPairs.push_back(pairs[left + i]);
    }
    for (size_t j = 0; j < sizeRight; ++j) {
      rightPairs.push_back(pairs[mid + 1 + j]);
    }

    size_t leftIndex = 0, rightIndex = 0, pairsIndex = left;
    while (leftIndex < sizeLeft && rightIndex < sizeRight) {
      if (leftPairs[leftIndex].first <= rightPairs[rightIndex].first) {
        pairs[pairsIndex++] = leftPairs[leftIndex++];
      } else {
        pairs[pairsIndex++] = rightPairs[rightIndex++];
      }
    }
    while (leftIndex < sizeLeft) {
      pairs[pairsIndex++] = leftPairs[leftIndex++];
    }
    while (rightIndex < sizeRight) {
      pairs[pairsIndex++] = rightPairs[rightIndex++];
    }
  }

  /**
   * Step 3: Insert values based on the Jacobsthal sequence.
   */
  template <typename T, typename U>
  static void insertJacobsthal(const T &pairs, U &sorted) {

    size_t pairsSize = pairs.size();
    size_t prevJacob = 0, currJacob = 1;

    sorted.push_back(pairs[0].second);
    sorted.push_back(pairs[0].first);
    if (pairsSize == 1) {
      return;
    }
    while (prevJacob < pairsSize) {
      insertLeaders(pairs, sorted, prevJacob, currJacob);
      insertFollowers(pairs, sorted, prevJacob, currJacob);
      size_t nextJacob = currJacob + 2 * prevJacob;
      prevJacob = currJacob;
      currJacob = nextJacob;
    }
  }

  template <typename T, typename U>
  static void insertLeaders(const T &pairs, U &sorted, size_t prevJacob,
                            size_t currJacob) {
    for (size_t i = prevJacob + 1; i < pairs.size() && i <= currJacob; ++i) {
      sorted.push_back(pairs[i].first);
    }
  }

  template <typename T, typename U>
  static void insertFollowers(const T &pairs, U &sorted, size_t prevJacob,
                              size_t currJacob) {
    if (currJacob < pairs.size()) {
      binaryInsertion(sorted, pairs[currJacob].second);
    }
    for (size_t i = prevJacob + 1; i < pairs.size() && i < currJacob; ++i) {
      binaryInsertion(sorted, pairs[i].second);
    }
  }

  /**
   * Step 4: Insert values using binary search (binary insertion).
   */
  template <typename U> static void binaryInsertion(U &sorted, int value) {
    typename U::iterator it;
    it = std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(it, value);
  }

  /**
   * Step 5: Execute the Merge Insertion Sort algorithm.
   */
  template <typename T, typename U>
  static void mergeInsertionSort(U &unsorted, T &pairs, U &sorted) {
    int singleElement = -1;
    if (unsorted.size() % 2 != 0) {
      singleElement = unsorted.back();
      unsorted.pop_back();
    }
    buildPairs(pairs, unsorted);
    mergeSortPairs(pairs, 0, pairs.size() - 1);
    insertJacobsthal(pairs, sorted);
    if (singleElement != -1) {
      binaryInsertion(sorted, singleElement);
    }
    unsorted = sorted;
  }
};
#endif // PMERGEME_HPP
