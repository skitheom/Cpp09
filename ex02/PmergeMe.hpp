#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include "GroupIterator.hpp"
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

  // std::list<Iterator> mainchain;
  // typedef typename std::list<Iterator>::iterator MainIt;
  std::list<Iterator> mainchain;
  typedef typename std::list<Iterator>::iterator MainIt;

  std::list<Follower<Iterator> > followers;
  typedef typename std::list<Follower<Iterator> >::iterator FollowerIt;

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
