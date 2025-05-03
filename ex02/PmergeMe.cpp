#include "PmergeMe.hpp"
#include "CmpInt.hpp"
#include "Log.hpp"
#include "PmergeMeDeq.hpp"
#include "PmergeMeVec.hpp"
#include "Print.hpp"
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace PmergeMe {

void parseInput(int size, const char **userInput, IntVec &vec) {
  vec.reserve(size);
  for (int i = 0; i < size; ++i) {
    char *endptr;
    errno = 0;
    long num = std::strtol(userInput[i], &endptr, 10);
    if (errno != 0 || num < 0 || num > std::numeric_limits<int>::max() ||
        *endptr != '\0') {
      std::ostringstream oss;
      oss << "Error: Invalid userInput: \"" << userInput[i] << "\"";
      throw std::runtime_error(oss.str());
    }
    CmpInt cmpInt(static_cast<int>(num));
    vec.push_back(cmpInt);
  }
}

double getTime(clock_t start, clock_t end) {
  return (static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC);
}

void sort(std::vector<CmpInt> &vec) {
  if (vec.size() < 2) {
    throw std::runtime_error("input must contain at least two values");
  }
  Log::log("\n=== Sorting vector ===");
  PmergeMeVec::mergeInsertionSort(vec, 1);
}

void sort(std::deque<CmpInt> &deq) {
  if (deq.size() < 2) {
    throw std::runtime_error("input must contain at least two values");
  }
  Log::log("\n=== Sorting deque ===");
  PmergeMeDeq::mergeInsertionSort(deq, 1);
}

void run(int size, const char **userInput) {
  IntVec vec;
  parseInput(size, userInput, vec);
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
  Print::printContainer("After (deq):  ", deq);


  std::cout << std::fixed << std::setprecision(1);
  std::cout << "Time to process a range of " << vec.size()
            << " elements with vector : " << getTime(vecStart, vecEnd)
            << " us, Comparison count: " << vecCmpCount << std::endl;
  std::cout << "Time to process a range of " << deq.size()
            << " elements with deque  : " << getTime(deqStart, deqEnd)
            << " us, Comparison count: " << deqCmpCount << std::endl;
}
} // namespace PmergeMe
