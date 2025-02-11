/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:48:53 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/11 03:18:58 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <utility>
class PmergeMe {
public:
  static void sort(std::vector<int> &vec);
  static void sort(std::deque<int> &deq);

private:
  PmergeMe();
  PmergeMe(const PmergeMe &other);
  ~PmergeMe();

  PmergeMe &operator=(const PmergeMe &other);

  static void mergeInsertionSort(std::vector<int> &vec);
  static void mergeInsertionSort(std::deque<int> &deq);

  template <typename T, typename U>
  static void buildPairs(T &pairs, const U &nums) {
    if (nums.size() % 2 != 0) {
      throw std::runtime_error("Error: Number of elements must be even");
    }
    for (typename U::const_iterator it = nums.begin(); it != nums.end(); ++it) {
      int a = *it;
      ++it;
      if (it == nums.end()) {
        throw std::runtime_error("Error: Unexpected end before making pair");
      }
      int b = *it;
      if (a < b) {
        std::swap(a, b);
      }
      pairs.push_back(std::make_pair(a, b));
    }
  }

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
    leftPairs.reserve(sizeLeft);
    rightPairs.reserve(sizeRight);

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

  template <typename T, typename U>
  static void insertFollowers(const T &pairs, U &sorted) {

    size_t indexToInsert, indexPairs, lastPos, realIndex;
    size_t pairCount = 0;
    size_t nthJacob = 0;
    size_t indexJacob = 0;
  }

  size_t jacobsthal(size_t n) {

    std::vector<int> jacobNums;

    jacobNums.reserve(n + 1);
    jacobNums[0] = 0;
    jacobNums[1] = 1;
    for (size_t i = 2; i <= n; ++i) {
      jacobNums[i] = jacobNums[i - 1] + 2 * jacobNums[i - 2];
    }
    return jacobNums[n];
  }
  template <typename T, typename U>
  static void jacobsthalInsertion(const T &pairs, U &sorted) {
    size_t prev1 = 0, prev2 = 1;

    if (n == 0) {
      return prev1;
    }
    if (n == 1) {
      return prev2;
    }
    for (size_t i = 2; i <= n; ++i) {
      size_t curr = prev2 + 2 * prev1;
      prev1 = prev2;
      prev2 = curr;
    }
    return prev2;
  }
};

#endif // PMERGEME_HPP
