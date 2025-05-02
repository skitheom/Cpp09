/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVec.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:24:50 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/02 14:10:06 by sakitaha         ###   ########.fr       */
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
  std::cout << std::endl;

  //  currJacob最小値=3, prevJacob最小値=1 のため安全
  for (size_t i = currJacob - 1; i >= prevJacob; --i) {
    if (i < pairs.size()) {
      std::cout << "\tInserting pairs[" << i
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
    std::cout << "[ prevJacob = " << prevJacob << ", currJacob = " << currJacob
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

void mergePairs(IntPairVec &pairs, size_t low, size_t mid, size_t high) {

  size_t i = low, j = mid + 1, k = 0;

  IntPairVec temp;
  temp.resize(high - low + 1);

  while ((i <= mid) && (j <= high)) {
    if (pairs[i].first < pairs[j].first) {
      temp[k++] = pairs[i++];
    } else {
      temp[k++] = pairs[j++];
    }
  }
  while (j <= high) {
    temp[k++] = pairs[j++];
  }
  while (i <= mid) {
    temp[k++] = pairs[i++];
  }
  for (i = low, k = 0; i <= high; i++, k++) {
    pairs[i] = temp[k];
  }
  temp.clear(); // しなくていいけど
}

void mergeSortPairs(IntPairVec &pairs, size_t low, size_t high) {
  if (low >= high) {
    return;
  }
  size_t mid = (low + high) / 2;
  mergeSortPairs(pairs, low, mid);
  mergeSortPairs(pairs, mid + 1, high);
  mergePairs(pairs, low, mid, high);
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
  Log::logContainer("After Insertion: ", vec);
  Log::log("Count: ", CmpInt::getComparisonCount() - prevCount);
  prevCount = CmpInt::getComparisonCount();
  Log::log("Total: ", CmpInt::getComparisonCount());
}

struct PairNode {
  CmpInt leadValue;
  struct PairNode *leader;
  struct PairNode *follower;
};

typedef std::vector<PairNode>::iterator PairsIt;
typedef std::vector<PairNode>::const_iterator ConstPairsIt;

void mergeInsertion(std::vector<PairNode> &prevPairs) {
  if (prevPairs.size() <= 1) {
    return;
  }
  std::vector<PairNode> pairs;
  pairs.reserve(prevPairs.size() / 2);

  for (size_t i = 0; i + 1 < prevPairs.size(); ++i) {
    struct PairNode node;
    if (prevPairs[i].leadValue > prevPairs[i + 1].leadValue) {
      node.leadValue = prevPairs[i].leadValue;
      node.leader = &prevPairs[i];
      node.follower = &prevPairs[i + 1];
    } else {
      node.leadValue = prevPairs[i + 1].leadValue;
      node.leader = &prevPairs[i + 1];
      node.follower = &prevPairs[i];
    }
    pairs.push_back(node);
  }

  bool hasIsolated = (prevPairs.size() % 2 != 0);
  struct PairNode isolated;
  if (hasIsolated) {
    isolated.leadValue = -1;
    isolated.leader = NULL;
    isolated.follower = &prevPairs[prevPairs.size() - 1];
  }

  mergeInsertion(pairs);

  // [...]
}

void mergeInsertionSortPairs(std::vector<PairNode> &pairs, size_t low, size_t high) {
  if (low >= high) {
    return;
  }
  size_t mid = (low + high) / 2;
  mergeSortPairs(pairs, low, mid);
  mergeSortPairs(pairs, mid + 1, high);
  mergePairs(pairs, low, mid, high);
}

void sort(IntVec &vec) {

  std::vector<PairNode> leafNodes;
  leafNodes.reserve(vec.size());

  for (ConstIntVecIt it = vec.begin(); it != vec.end(); ++it) {
    struct PairNode node;
    node.leadValue = *it;
    node.leader = NULL;
    node.follower = NULL;
    leafNodes.push_back(node);
  }

  std::vector<PairNode> pairs;
  pairs.reserve(leafNodes.size() / 2);

  for (size_t i = 0; i + 1 < leafNodes.size(); ++i) {
    struct PairNode node;
    if (leafNodes[i].leadValue > leafNodes[i + 1].leadValue) {
      node.leadValue = leafNodes[i].leadValue;
      node.leader = &leafNodes[i];
      node.follower = &leafNodes[i + 1];
    } else {
      node.leadValue = leafNodes[i + 1].leadValue;
      node.leader = &leafNodes[i + 1];
      node.follower = &leafNodes[i];
    }
    pairs.push_back(node);
  }

  bool hasIsolated = (leafNodes.size() % 2 != 0);
  struct PairNode isolated;
  if (hasIsolated) {
    isolated.leadValue = -1;
    isolated.leader = NULL;
    isolated.follower = &leafNodes[leafNodes.size() - 1];
  }

  mergeInsertion(pairs);

  std::vector<PairNode> main_chain;
  std::vector<PairNode> unsorted;
}

} // namespace PmergeMeVec

/*
消したところ


// IntPairVec pairs;
  // pairs.reserve(vec.size() / 2 + 1);

  // Log::log("\nSorting vector ...");
  // mergeInsertionSort(pairs, vec);

  if (singleElement != -1) {
    // binaryInsertion(vec, vec.size(), singleElement);
    IntVecIt pos = std::lower_bound(vec.begin(), vec.end(), singleElement);
    vec.insert(pos, singleElement);
    Log::log("\nInserting single element: ", singleElement.getValue());
    Log::log("Count: ", CmpInt::getComparisonCount() - prevCount);
    Log::log("Total: ", prevCount = CmpInt::getComparisonCount());
  }
*/
