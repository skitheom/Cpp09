#include "PmergeMeVec.hpp"
#include "Log.hpp"

namespace PmergeMeVec {

typedef std::vector<IntVecIt> MainChain;
typedef MainChain::iterator MainIt;
typedef std::vector<IntVecIt> Followers;
typedef Followers::iterator FollowersIt;

void swapGroups(IntVecIt lhsIt, IntVecIt rhsIt, size_t prevGroupSize) {
  std::swap_ranges(lhsIt, lhsIt + prevGroupSize, rhsIt);
}

IntVecIt groupFirstIt(IntVec &vec, size_t groupLastIdx, size_t groupSize) {
  return vec.begin() + groupLastIdx + 1 - groupSize;
}

IntVecIt groupLastIt(IntVec &vec, size_t groupFirstIdx, size_t groupSize) {
  return vec.begin() + groupFirstIdx + groupSize - 1;
}

IntVecIt groupFirstIt(IntVecIt groupLastIt, size_t groupSize) {
  return groupLastIt + 1 - groupSize;
}

IntVecIt groupLastIt(IntVecIt groupFirstIt, size_t groupSize) {
  return groupFirstIt + groupSize - 1;
}

bool cmpByValue(const IntVecIt &a, const IntVecIt &b) { return *a < *b; }

void binaryInsertion(MainChain &mainchain, const size_t end, IntVecIt it) {
  MainIt endIt = mainchain.begin();
  std::advance(endIt, end);

  MainIt insertPos = std::lower_bound(mainchain.begin(), endIt, it, cmpByValue);
  mainchain.insert(insertPos, it);
}

void mergeInsertionSort(IntVec &vec, size_t prevGroupSize) {

  size_t currGroupSize = prevGroupSize * 2;

  if (currGroupSize > vec.size()) {
    Log::log("\nGroup size limit reached", currGroupSize);
    return;
  }

  ////////////////////////////////////////////////////////////
  // Form groups by pairing adjacent subgroups

  for (size_t rhsIdx = currGroupSize - 1; rhsIdx < vec.size();
       rhsIdx += currGroupSize) {

    size_t lhsIdx = rhsIdx - prevGroupSize;

    if (vec[lhsIdx] > vec[rhsIdx]) {
      IntVecIt lhsIt = groupFirstIt(vec, lhsIdx, prevGroupSize);
      IntVecIt rhsIt = groupFirstIt(vec, rhsIdx, prevGroupSize);
      swapGroups(lhsIt, rhsIt, prevGroupSize);
    }
  }

  Log::log("\nForming groups of size", currGroupSize);
  Log::logContainer("Grouped pairs: \t", vec);

  ////////////////////////////////////////////////////////////
  // Recursively sort the group leaders

  mergeInsertionSort(vec, currGroupSize);

  ////////////////////////////////////////////////////////////
  // Binary insertion into the main chain

  // NOTE:
  // leaderIdx 初期値 = currGroupSize - 1;
  // leaderIdx は常に = 初期値 + currGroupSize * i;
  // followIdx は常に = leaderIdx - prevGroupSize;

  MainChain mainchain; // keeps lastIt of each group
  Followers followers;

  IntVecIt firstFollowerIt = groupLastIt(vec, 0, prevGroupSize);           // F0
  IntVecIt firstLeaderIt = groupLastIt(vec, prevGroupSize, prevGroupSize); // L0

  mainchain.push_back(firstFollowerIt);
  mainchain.push_back(firstLeaderIt);

  size_t prevJacob = 1, currJacob = 3, leaderIdx = 0;
  const size_t limit = prevGroupSize * (vec.size() / prevGroupSize);
  bool reachedEnd = false; // if true, no more leaders to insert

  Log::log("\nBinary insertion into mainchain for pairs of size:",
           currGroupSize);

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
        mainchain.push_back(vec.begin() + leaderIdx);
      }

      if (followIdx < limit) {
        followers.push_back(vec.begin() + followIdx);
      }
    }

    // insert followers back to mainchain backwards
    const size_t searchEnd =
        (leaderIdx < limit) ? mainchain.size() - 1 : mainchain.size();

    while (!followers.empty()) {
      IntVecIt followerIt = followers.back();
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

  IntVec cache;
  cache.reserve(vec.size());

  Log::log("\nCopying back cached paris of size", currGroupSize);
  Log::logContainer("Before overwrite: ", vec);

  // mainchainのitは、各groupの右端（代表）を指しているので注意
  for (MainIt mainIt = mainchain.begin(); mainIt != mainchain.end(); ++mainIt) {
    IntVecIt lastIt = *mainIt;
    IntVecIt firstIt = groupFirstIt(lastIt, prevGroupSize);
    std::copy(firstIt, lastIt + 1, std::back_inserter(cache));
  }
  std::copy(cache.begin(), cache.end(), vec.begin());

  Log::logContainer("Overwritten section: ", vec);
}
} // namespace PmergeMeVec
