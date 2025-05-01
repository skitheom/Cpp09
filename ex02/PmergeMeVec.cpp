/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVec.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:24:50 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/01 19:35:30 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMeVec.hpp"
#include "Log.hpp"
#include <utility>

namespace PmergeMeVec {

// 終端を指定し、二分探索で値を入れる
void binaryInsertion(IntVec &vec, const size_t searchEnd, const CmpInt &value) {
  int prevCount = CmpInt::getComparisonCount();
  // std::cout << "探索範囲: ";
  // for (size_t i = 0; i < searchEnd; ++i) {
  //   std::cout << vec[i] << " ";
  // }
  // std::cout << " | 対象の要素数: " << searchEnd;
  IntVecIt pos = std::lower_bound(vec.begin(), vec.begin() + searchEnd, value);
  vec.insert(pos, value);
  std::cout << " \t|\t比較回数: " << CmpInt::getComparisonCount() - prevCount
            << "\n";
}

// current Jacobsthal number - 1 までの Followers を挿入
void insertFollowers(const IntPairVec &pairs, IntVec &vec, size_t prevJacob,
                     size_t currJacob) {

  // フォロワーは常に対応するリーダーより小さいため、フォロワー挿入時に対応するリーダーは
  // 探索範囲から除外できる。後ろから順にフォロワーを挿入するため、searchEndは常に一定
  const size_t searchEnd = vec.size() - 1;

  //  currJacob最小値=3, prevJacob最小値=1 のため安全
  for (size_t i = currJacob - 1; i >= prevJacob; --i) {
    if (i < pairs.size()) {
      std::cout << "\n\tInserting pairs[" << i
                << "].follower = " << pairs[i].second;
      binaryInsertion(vec, searchEnd, pairs[i].second);
    }
  }
}

// current Jacobsthal number - 1 までの Leaders を挿入
void insertLeaders(const IntPairVec &pairs, IntVec &vec, size_t prevJacob,
                   size_t currJacob, bool hasIsolated) {
  size_t leadersSize = hasIsolated ? pairs.size() - 1 : pairs.size();
  for (size_t i = prevJacob; i < currJacob && i < leadersSize; ++i) {
    vec.push_back(pairs[i].first);
  }
}

void insertJacobsthal(const IntPairVec &pairs, IntVec &vec, bool hasIsolated) {

  size_t pairsSize = pairs.size();

  vec.push_back(pairs[0].second);
  vec.push_back(pairs[0].first);
  if (pairsSize == 1 && !hasIsolated) {
    return;
  }
  Log::logContainer("\n=== insertJacobsthal ===\nAfter insertpairs[0] : ", vec);

  // Jacobsthal Number: 0 1 1 3 5 11 21 43 85 171 341 ... ♾️
  // pairs[0]は処理済み prev = 1, curr = 1 は skipのため
  size_t prevJacob = 1, currJacob = 3;

  while (prevJacob < pairsSize) {
    std::cout << "\n[ prevJacob=" << prevJacob << ", currJacob=" << currJacob
              << " ]" << std::endl;
    insertLeaders(pairs, vec, prevJacob, currJacob, hasIsolated);
    Log::logContainer("After insertLeaders  : ", vec);
    insertFollowers(pairs, vec, prevJacob, currJacob);
    Log::logContainer("\nAfter insertFollowers: ", vec);
    size_t nextJacob = currJacob + 2 * prevJacob;
    prevJacob = currJacob;
    currJacob = nextJacob;
    std::cout << "\n";
  }
}

void mergePairs(IntPairVec &pairs, size_t left, size_t mid, size_t right) {

  IntPairVec leftPairs;
  IntPairVec rightPairs;
  size_t sizeLeft = mid - left + 1;
  size_t sizeRight = right - mid;

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

void mergeSortPairs(IntPairVec &pairs, size_t left, size_t right) {
  if (left >= right) {
    return;
  }
  size_t mid = left + (right - left) / 2;
  mergeSortPairs(pairs, left, mid);
  mergeSortPairs(pairs, mid + 1, right);
  mergePairs(pairs, left, mid, right);
}

void buildPairs(IntPairVec &pairs, IntVec &vec) {

  for (size_t i = 0; i + 1 < vec.size(); i += 2) {
    IntPair p;
    p.first = vec[i];
    p.second = vec[i + 1];
    if (p.first < p.second) {
      std::swap(p.first, p.second);
    }
    pairs.push_back(p);
  }
}

void mergeInsertionSort(IntPairVec &pairs, IntVec &vec) {

  IntPair isolated(-1, -1);
  bool hasIsolated = false;

  if (vec.size() % 2 != 0) {
    isolated.second = vec.back();
    hasIsolated = true;
    vec.pop_back(); // 消す必要はないのかも
    Log::log("Single element: ", isolated.second);
  }

  int prevCount = CmpInt::getComparisonCount();

  buildPairs(pairs, vec);
  vec.clear();
  vec.reserve(pairs.size() * 2 + 1);
  Log::logPairs("\nAfter buildpairs: ", pairs);
  Log::log("Count: ", CmpInt::getComparisonCount() - prevCount);
  prevCount = CmpInt::getComparisonCount();

  mergeSortPairs(pairs, 0, pairs.size() - 1);
  Log::logPairs("\nAfter Mergesort : ", pairs);
  Log::log("Count: ", CmpInt::getComparisonCount() - prevCount);
  prevCount = CmpInt::getComparisonCount();

  if (hasIsolated) {
    pairs.push_back(isolated);
    Log::logPairs("\nAfter adding isolated value : ", pairs);
    Log::log("Count: ", CmpInt::getComparisonCount() - prevCount);
    prevCount = CmpInt::getComparisonCount();
  }

  insertJacobsthal(pairs, vec, hasIsolated);
  Log::logContainer("\nAfter Insertion: ", vec);
  Log::log("Count: ", CmpInt::getComparisonCount() - prevCount);
  prevCount = CmpInt::getComparisonCount();
  Log::log("Total: ", CmpInt::getComparisonCount());
}

void sort(IntVec &vec) {
  IntPairVec pairs;
  pairs.reserve(vec.size() / 2 + 1);

  Log::log("\nSorting vector ...");
  mergeInsertionSort(pairs, vec);
}

} // namespace PmergeMeVec

/*
消したところ

  if (singleElement != -1) {
    // binaryInsertion(vec, vec.size(), singleElement);
    IntVecIt pos = std::lower_bound(vec.begin(), vec.end(), singleElement);
    vec.insert(pos, singleElement);
    Log::log("\nInserting single element: ", singleElement.getValue());
    Log::log("Count: ", CmpInt::getComparisonCount() - prevCount);
    Log::log("Total: ", prevCount = CmpInt::getComparisonCount());
  }
*/
