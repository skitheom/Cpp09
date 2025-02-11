/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:48:53 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/11 19:32:07 by sakitaha         ###   ########.fr       */
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

  /**
   * jacobthalに基づいて、leadersはちょっとずつpushされる
   * prevJaobより大きく、currJaboc以下のindexPosのleadersをpushする
   */
  template <typename T, typename U>
  static void insertLeaders(const T &pairs, U &sorted, size_t prevJacob,
                            size_t currJacob) {
    for (size_t i = prevJacob + 1; i < pairs.size() && i <= currJacob; ++i) {
      sorted.push_back(pairs[i].first);
    }
  }

  /**
   * jacobthalのindexPosにあるfollower値を、先にsortedに挿入
   * 残りの部分は、indexのより小さいものから順番にbinaryInsertion
   * prevJaobより大きく、currJaboc以下のindexPosのfollowersが対象
   */
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

  template <typename U> static void binaryInsertion(U &sorted, int value) {
    typename U::iterator it;
    it = std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(it, value);
  }

  template <typename T, typename U>
  static void insertJacobsthal(const T &pairs, U &sorted) {

    size_t pairsSize = pairs.size();
    size_t prevJacob = 0, currJacob = 1;

    sorted.push_back(pairs[0].second); // pairs[0]のfollowerは最小値
    sorted.push_back(pairs[0].first);  // index処理をfolower/leaderで揃えるため
    if (pairsSize == 1) {
      return;
    }
    // prevJacobがpairsSize未満 = 未ソート値あり
    while (prevJacob < pairsSize) {
      // prevJacobsthal値より大きく、currJacob以下のindexPosのleadersを挿入
      insertLeaders(pairs, sorted, prevJacob, currJacob);
      // prevJacobshtal値より大きく、currJacob以下のindexPosのfollowersを挿入
      insertFollowers(pairs, sorted, prevJacob, currJacob);
      // 次のJacobsthal numberを用意しておく
      size_t nextJacob = currJacob + 2 * prevJacob;
      prevJacob = currJacob;
      currJacob = nextJacob;
    }
  }

  template <typename T, typename U>
  static void mergeInsertionSort(T &pairs, U &unsorted, U &sorted) {

      // 1.pairを作る


  }

  /*
  Jaobsthal number 参考値
  初期値: prev: 0, curr: 1
  i = 0: prev: 1, curr: 1 この呼び出しが無意味？ 1より大きく1以下は存在しない
  i = 1: prev: 1, curr: 3
  i = 2: prev: 3, curr: 5
  i = 3: prev: 5, curr: 11
  i = 4: prev: 11, curr: 21
  i = 5: prev: 21, curr: 43
  i = 6: prev: 43, curr: 85
  */
};

#endif // PMERGEME_HPP
