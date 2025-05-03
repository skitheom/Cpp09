#include "PmergeMe.hpp"
#include "Log.hpp"
#include "Print.hpp"
#include "Utils.hpp"
#include <iomanip>

namespace PmergeMe {

void sort(std::vector<CmpInt> &vec) {
  mergeInsertionSort(vec, vec.begin(), vec.end());
}

void sort(std::deque<CmpInt> &deq) {
  IntVec vec(deq.begin(), deq.end());
  return ;
  mergeInsertionSort(vec, deq.begin(), deq.end());
}

void run(int size, const char **userInput) {
  IntVec vec;
  Utils::parseInput(size, userInput, vec);
  IntDeq deq(vec.begin(), vec.end());

  Print::printContainer("Before (vec): ", vec);
  Log::logContainer("Before (deq): ", deq);

  CmpInt::resetComparisons();
  clock_t vecStart = clock();
  sort(vec);
  clock_t vecEnd = clock();
  int vecCmpCount = CmpInt::getComparisonCount();

  CmpInt::resetComparisons();
  clock_t deqStart = clock();
  sort(deq);
  clock_t deqEnd = clock();
  int deqCmpCount = CmpInt::getComparisonCount();

  Print::printContainer("After (vec):  ", vec);
  Log::logContainer("After (deq):  ", deq);

  std::cout << std::fixed << std::setprecision(1);
  std::cout << "Time to process a range of " << vec.size()
            << " elements with vector : " << Utils::getTime(vecStart, vecEnd)
            << " us, Comparison count: " << vecCmpCount << std::endl;
  std::cout << "Time to process a range of " << deq.size()
            << " elements with deque  : " << Utils::getTime(deqStart, deqEnd)
            << " us, Comparison count: " << deqCmpCount << std::endl;
}
} // namespace PmergeMe
