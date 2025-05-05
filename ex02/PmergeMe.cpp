#include "PmergeMe.hpp"
#include "CmpInt.hpp"
#include "Log.hpp"
#include "PmergeMeDeq.hpp"
#include "PmergeMeVec.hpp"
#include "Print.hpp"
#include <algorithm>
#include <cerrno>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace PmergeMe {

void parseInput(int size, const char **userInput, IntVec &vec) {
  vec.reserve(size);
  for (int i = 0; i < size; ++i) {
    if (userInput[i][0] == '\0') {
      std::ostringstream oss;
      oss << "Invalid userInput: \"" << userInput[i] << "\"";
      throw std::runtime_error(oss.str());
    }

    char *endptr;
    errno = 0;
    long num = std::strtol(userInput[i], &endptr, 10);
    if (errno != 0 || num < 0 || num > std::numeric_limits<int>::max() ||
        *endptr != '\0') {
      std::ostringstream oss;
      oss << "Invalid userInput: \"" << userInput[i] << "\"";
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
  IntVec vecCopy = vec;
  IntDeq deqCopy = deq;

  Print::printContainer("Before:\t", vec);

  // vector sort
  CmpInt::resetComparisons();
  clock_t vecStart = clock();
  sort(vec);
  clock_t vecEnd = clock();
  int vecCmpCount = CmpInt::getComparisonCount();

  // deq sort
  CmpInt::resetComparisons();
  clock_t deqStart = clock();
  sort(deq);
  clock_t deqEnd = clock();
  int deqCmpCount = CmpInt::getComparisonCount();

  Print::printContainer("After :\t", vec);
  // Print::printContainer("After (deq):  ", deq);

  std::cout << std::fixed << std::setprecision(1);
  std::cout << "Time to process a range of " << vec.size()
            << " elements with vector : " << getTime(vecStart, vecEnd)
            << " us, Comparison count: " << vecCmpCount << std::endl;
  std::cout << "Time to process a range of " << deq.size()
            << " elements with deque  : " << getTime(deqStart, deqEnd)
            << " us, Comparison count: " << deqCmpCount << std::endl;

  std::sort(vecCopy.begin(), vecCopy.end());
  std::sort(deqCopy.begin(), deqCopy.end());

  bool vecOK = (vec == vecCopy);
  bool deqOK = std::equal(deq.begin(), deq.end(), deqCopy.begin());

  std::cout << "Result (vec):  " << (vecOK ? GREEN "OK" : RED "NG") << RESET
            << std::endl;
  std::cout << "Result (deq):  " << (deqOK ? GREEN "OK" : RED "NG") << RESET
            << std::endl;
}
} // namespace PmergeMe

/*

$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us
$> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
Before: 141 79 526 321 [...]
After: 79 141 321 526 [...]
Time to process a range of 3000 elements with std::[..] : 62.14389 us
Time to process a range of 3000 elements with std::[..] : 69.27212 us
$> ./PmergeMe "-1" "2"
Error
$> # For OSX USER:
$> ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
[...]
$>

*/