#include "PmergeMeDeq.hpp"
#include "Log.hpp"
#include "PmergeMeVec.hpp"
#include <algorithm>

namespace PmergeMeDeq {

typedef std::deque<IntDeqIt> MainChain;
typedef MainChain::iterator MainIt;
typedef std::deque<IntDeqIt> Followers;
typedef Followers::iterator FollowersIt;

void swapGroups(IntDeqIt lhsIt, IntDeqIt rhsIt, size_t prevGroupSize) {
  std::swap_ranges(lhsIt, lhsIt + prevGroupSize, rhsIt);
}

IntDeqIt groupFirstIt(IntDeq &deq, size_t groupLastIdx, size_t groupSize) {
  return deq.begin() + groupLastIdx + 1 - groupSize;
}

IntDeqIt groupLastIt(IntDeq &deq, size_t groupFirstIdx, size_t groupSize) {
  return deq.begin() + groupFirstIdx + groupSize - 1;
}

IntDeqIt groupFirstIt(IntDeqIt groupLastIt, size_t groupSize) {
  return groupLastIt + 1 - groupSize;
}

IntDeqIt groupLastIt(IntDeqIt groupFirstIt, size_t groupSize) {
  return groupFirstIt + groupSize - 1;
}

bool cmpByValue(const IntDeqIt &a, const IntDeqIt &b) { return *a < *b; }

void binaryInsertion(MainChain &mainchain, const size_t end, IntDeqIt it) {
  MainIt endIt = mainchain.begin();
  std::advance(endIt, end);

  MainIt insertPos = std::lower_bound(mainchain.begin(), endIt, it, cmpByValue);
  mainchain.insert(insertPos, it);
}

void mergeInsertionSort(IntDeq &deq, size_t prevGroupSize) {

  size_t currGroupSize = prevGroupSize * 2;

  if (currGroupSize > deq.size()) {
    Log::log("\nGroup size limit reached", currGroupSize);
    return;
  }

  ////////////////////////////////////////////////////////////
  // Form groups by pairing adjacent subgroups

  for (size_t rhsIdx = currGroupSize - 1; rhsIdx < deq.size();
       rhsIdx += currGroupSize) {

    size_t lhsIdx = rhsIdx - prevGroupSize;

    if (deq[lhsIdx] > deq[rhsIdx]) {
      IntDeqIt lhsIt = groupFirstIt(deq, lhsIdx, prevGroupSize);
      IntDeqIt rhsIt = groupFirstIt(deq, rhsIdx, prevGroupSize);
      swapGroups(lhsIt, rhsIt, prevGroupSize);
    }
  }

  Log::log("\nForming groups of size", currGroupSize);
  Log::logContainer("Grouped pairs: \t", deq);

  ////////////////////////////////////////////////////////////
  // Recursively sort the group leaders

  mergeInsertionSort(deq, currGroupSize);

  ////////////////////////////////////////////////////////////
  // Binary insertion into the main chain

  // NOTE:
  // leaderIdx 初期値 = currGroupSize - 1;
  // leaderIdx は常に = 初期値 + currGroupSize * i;
  // followIdx は常に = leaderIdx - prevGroupSize;

  MainChain mainchain; // keeps lastIt of each group
  Followers followers;

  IntDeqIt firstFollowerIt = groupLastIt(deq, 0, prevGroupSize);           // F0
  IntDeqIt firstLeaderIt = groupLastIt(deq, prevGroupSize, prevGroupSize); // L0

  mainchain.push_back(firstFollowerIt);
  mainchain.push_back(firstLeaderIt);

  size_t prevJacob = 1, currJacob = 3, leaderIdx = 0;
  const size_t limit = prevGroupSize * (deq.size() / prevGroupSize);
  bool reachedEnd = false; // if true, no more leaders to insert

  while (!reachedEnd) {
    // insert leaders and pend followers
    // N=prevJacob, M=currJacob: Nth, N+1th, ... , M-1th
    for (size_t i = prevJacob; i < currJacob; ++i) {

      leaderIdx = currGroupSize - 1 + currGroupSize * i;
      size_t followIdx = leaderIdx - prevGroupSize;

      if (leaderIdx >= limit && followIdx >= limit) {
        reachedEnd = true;
        break;
      }

      if (leaderIdx < limit) {
        mainchain.push_back(deq.begin() + leaderIdx);
      }

      if (followIdx < limit) {
        followers.push_back(deq.begin() + followIdx);
      }
    }

    // insert followers back to mainchain backwards
    const size_t searchEnd =
        (leaderIdx < limit) ? mainchain.size() - 1 : mainchain.size();

    while (!followers.empty()) {
      IntDeqIt followerIt = followers.back();
      followers.pop_back();
      binaryInsertion(mainchain, searchEnd, followerIt);
    }

    // calculate next Jacobsthal number
    size_t nextJacob = currJacob + 2 * prevJacob;
    prevJacob = currJacob;
    currJacob = nextJacob;
  }

  ////////////////////////////////////////////////////////////
  // Move values in order to a cache then back to origin

  IntDeq cache;

  // mainchainのitは、各groupの右端（代表）を指しているので注意
  for (MainIt mainIt = mainchain.begin(); mainIt != mainchain.end(); ++mainIt) {
    IntDeqIt lastIt = *mainIt;
    IntDeqIt firstIt = groupFirstIt(lastIt, prevGroupSize);
    std::copy(firstIt, lastIt + 1, std::back_inserter(cache));
  }
  std::copy(cache.begin(), cache.end(), deq.begin());

  Log::log("\nCopying back cached paris of size", currGroupSize);
  Log::logContainer("Overwritten section: ", deq);
}
} // namespace PmergeMeDeq
