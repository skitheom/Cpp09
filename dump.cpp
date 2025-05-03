#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include "Log.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

namespace PmergeMe {

template <typename Iterator> struct Follower {
  Iterator followerIt;
  typename std::list<Iterator>::iterator searchEnd;
};

template <typename Iterator>
void mergeInsertionSortImpl(std::vector<CmpInt> &vec, Iterator first,
                            Iterator last) {

  typedef typename GroupIterator<Iterator>::difference_type DiffType;

  DiffType size = std::distance(first, last);
  if (size < 2) {
    return;
  }

  bool hasIsolated = (size % 2 != 0);

  ////////////////////////////////////////////////////////////
  // Group elements by pairs

  using std::iter_swap;

  // Iterator=GroupIteratorなら、GroupIterator::iter_swapが呼ばれる
  Iterator end = hasIsolated ? last - 1 : last;
  for (Iterator it = first; it != end; it += 2) {
    if (it[1] < it[0]) {
      iter_swap(it, it + 1);
    }
  }

  Log::log("Group size: ", first.size());
  Log::logContainer("Step  1: ", vec);

  ////////////////////////////////////////////////////////////
  // 代表値 (Leaders) を基準にして、ペアを再帰敵にソート
  mergeInsertionSortImpl(vec, makeGroupIt(first, 2), makeGroupIt(end, 2));

  ////////////////////////////////////////////////////////////
  // Separate main chain and pend elements

  std::list<Iterator> mainchain;
  typedef typename std::list<Iterator>::iterator MainIt;

  std::list<Follower<Iterator>> followers;
  typedef typename std::list<Follower<Iterator>>::iterator FollowerIt;

  mainchain.push_back(first);     // follower[0]
  mainchain.push_back(first + 1); // leader[0]

  for (Iterator it = first + 2; it != end; it += 2) {
    if (it + 1 < last) {
      // mainchainの末尾にleaderを追加　it: follower, it+1: leader
      MainIt tmp = mainchain.insert(mainchain.end(), it + 1);
      struct Follower<Iterator> follower;
      follower.followerIt = it;
      follower.searchEnd = tmp;
      followers.push_back(follower); // leaderが mainchain のどこに入ったか記録
    }
  }

  if (hasIsolated) {
    struct Follower<Iterator> isolated;
    isolated.followerIt = end;
    isolated.searchEnd = mainchain.end();
    followers.push_back(isolated);
  }

  ////////////////////////////////////////////////////////////
  // Binary insertion into the main chain

  size_t prevJacob = 1, currJacob = 3;

  while (true) {
    size_t dist = currJacob - prevJacob;
    if (dist >= followers.size()) {
      break;
    }

    FollowerIt it = followers.begin();
    std::advance(it, dist);
    MainIt searchEnd = it->searchEnd;

    while (true) {
      MainIt insertPoint =
          std::lower_bound(mainchain.begin(), searchEnd, it->followerIt);
      mainchain.insert(insertPoint, it->followerIt);

      it = followers.erase(it);
      if (it == followers.begin() || searchEnd == mainchain.begin()) {
        break;
      }
      --it;
      --searchEnd;
    }
    size_t nextJacob = currJacob + 2 * prevJacob; // Jacobsthalの計算
    prevJacob = currJacob;
    currJacob = nextJacob;
  }

  while (!followers.empty()) {
    FollowerIt it = followers.end();
    --it;
    MainIt insertPoint =
        std::lower_bound(mainchain.begin(), it->searchEnd, it->followerIt);
    mainchain.insert(insertPoint, it->followerIt);
    followers.pop_back();
  }

  for (MainIt it = mainchain.begin(); it != mainchain.end(); ++it) {
    std::cout << "[main chain] group base: " << &(*it->base())
              << ", size: " << it->size()
              << ", leader (representative): " << **it << std::endl;

    for (std::size_t i = 0; i < it->size(); ++i) {
      std::cout << "  [main chain] offset: " << i
                << ", value: " << *(it->base() + i) << std::endl;
    }
  }

  ////////////////////////////////////////////////////////////
  // Move values in order to a cache then back to origin

  typedef typename std::iterator_traits<Iterator>::value_type ValueType;
  std::vector<ValueType> cache;
  cache.reserve(size);

  typedef typename Iterator::iterator_type InnerIt;

  for (MainIt it = mainchain.begin(); it != mainchain.end(); ++it) {

    InnerIt begin = it->base();
    break;
    if (begin < first.base() || begin >= last.base()) {
      std::cerr << "[ERROR] Invalid base() pointer!" << std::endl;
      assert(false); // デバッグ用
    }
    std::cout << "[DEBUG] group begin address: " << &(*begin)
              << ", size: " << it->size() << std::endl;

    // for (std::size_t i = 0; i < it->size(); ++i) {
    //   std::cout << "  [DEBUG] offset: " << i << ", value: " << *(begin + i)
    //             << std::endl;
    //   //cache.push_back(*(begin + i));
    // }
    std::copy(it->base(), it->base() + it->size(), std::back_inserter(cache));
  }
  Log::logContainer("Before copy: ", vec);
  // cache を元の範囲に書き戻す
  std::copy(cache.begin(), cache.end(), first);
  Log::logContainer("After copy : ", vec);
}

/*

    std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type>
   cache; cache.reserve(size);

    for (auto&& it: chain)
    {
        auto begin = it.base();
        auto end = begin + it.size();
        std::move(begin, end, std::back_inserter(cache));
    }
    std::move(std::begin(cache), std::end(cache), first.base());

*/

template <typename Iterator>
void mergeInsertionSort(std::vector<CmpInt> &vec, Iterator first,
                        Iterator last) {
  // 一番最初のみ size=1 (ペアのないグループ)
  Log::logContainer("Step  0: ", vec);
  ;
  mergeInsertionSortImpl(vec, makeGroupIt(first, 1), makeGroupIt(last, 1));
}

void run(int size, const char **userInput);
} // namespace PmergeMe

#endif // PMERGE_ME_HPP

/*
// lhs と rhs の各 group（size 個分の要素）を一括で入れ替える
template <typename Iterator1, typename Iterator2>
void iter_swap(GroupIterator<Iterator1> lhs, GroupIterator<Iterator2> rhs) {
  std::swap_ranges(lhs.base(), lhs.base() + lhs.size(), rhs.base());
}


*/

// // lhsLastIt, rhsLastIt は要素を構成するグループの右端（リーダー）を指す
// // 各グループの左端から prevGroupSize 要素分を swap する
// template <typename Iterator>
// void swapGroups(Iterator lhsLastIt, Iterator rhsLastIt, size_t prevGroupSize)
// {
//   Iterator lhsFirstIt = lhsLastIt + 1 - prevGroupSize;
//   Iterator rhsFirstIt = rhsLastIt + 1 - prevGroupSize;
//   std::swap_ranges(lhsFirstIt, lhsFirstIt + prevGroupSize, rhsFirstIt);
// }

#include "Log.hpp"
#include "PmergeMeVec.hpp"
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
  }
}

IntVecIt groupFirstIt(IntVec &vec, size_t groupLastIdx, size_t groupSize) {
  return vec.begin() + groupLastIdx + 1 - groupSize;
}

IntVecIt groupLastIt(IntVec &vec, size_t groupFirstIdx, size_t groupSize) {
  return vec.begin() + groupFirstIdx + groupSize - 1;
}
IntVecIt firstFollowerIt = vec.begin() + prevGroupSize - 1; // F[0]
IntVecIt firstLeaderIt = vec.begin() + currGroupSize - 1;   // L[0]

size_t isolatedLeaderIdx;
bool hasIsolated = (vec.size() % currGroupSize) >= prevGroupSize;

if (hasIsolated) {
  size_t isolatedStartIdx = vec.size() - (vec.size() % currGroupSize);
  isolatedLeaderIdx = isolatedStartIdx + prevGroupSize - 1;
}

// フォロワーは常に対応するリーダーより小さいため、フォロワーに対応するリーダーは
// 探索範囲から除外。後ろから順にフォロワーを挿入するため、searchEndは一定にできる
// いま入ってるleaderまでを最初のsearch範囲として設定して、そのまま維持できる
// たとえば, prevJacob=1, currJacob=3の時
// b2 を入れる時に、{b0, a0, a1, | a2} b0-a1の検索範囲=3で挿入できる
// b1
// を入れる時に、仮にb2がどこに入ったとしても、b0-xxの検索範囲=3で挿入できる
// {b0, a0, a1, | b2, a2}, {b0, a0, b2, | a1, a2}, {b0, b2, a0, | a1, a2}


size_t prevJacob = 1, currJacob = 3;

while (true) {
  bool reachedEnd = true;

  for (size_t i = prevJacob; i < currJacob; ++i) {
    size_t leaderIdx = currGroupSize - 1 + currGroupSize * i;
    size_t followIdx = leaderIdx - prevGroupSize;

    if (leaderIdx >= vec.size()) {
      if (followIdx < vec.size()) {
        followers.push_back(vec.begin() + followIdx); // isolated
        reachedEnd = false;
      }
      break;
    }

    mainchain.push_back(vec.begin() + leaderIdx);
    followers.push_back(vec.begin() + followIdx);
    reachedEnd = false;
  }

  const size_t searchEnd = mainchain.size() - 1;

  while (!followers.empty()) {
    IntVecIt followerIt = followers.back();
    followers.pop_back();
    binaryInsertion(mainchain, searchEnd, followerIt);
  }

  if (reachedEnd)
    break;

  size_t nextJacob = currJacob + 2 * prevJacob;
  prevJacob = currJacob;
  currJacob = nextJacob;
}


for (size_t i = prevJacob; i < currJacob; ++i) {
  leaderIdx = currGroupSize - 1 + currGroupSize * i;

  size_t leaderIdxLocal = currGroupSize - 1 + currGroupSize * i;
leaderIdx = leaderIdxLocal; // if you still want to track latest global


size_t leaderIdxLocal = currGroupSize - 1 + currGroupSize * i;
leaderIdx = leaderIdxLocal; // if you still want to track latest global


if (leaderIdx >= vec.size()) {
  if (followIdx < vec.size()) {
    // last group has a follower only (isolated case)
    followers.push_back(vec.begin() + followIdx);
  }
  break;
}


// lhsIt, rhsIt はグループの左端を指し、 prevGroupSize 要素分を swap する
template <typename Iterator>
void swapGroups(Iterator lhsIt, Iterator rhsIt, size_t prevGroupSize) {
  std::swap_ranges(lhsIt, lhsIt + prevGroupSize, rhsIt);
}

IntVecIt groupFirstIt(IntVec &vec, size_t groupLastIdx, size_t groupSize) {
  return vec.begin() + groupLastIdx + 1 - groupSize;
}

IntVecIt groupLastIt(IntVec &vec, size_t groupFirstIdx, size_t groupSize) {
  return vec.begin() + groupFirstIdx + groupSize - 1;
}
