/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:33:08 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/11 01:0 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
  if (this != &other) {
  }
  return *this;
}

void PmergeMe::sort(std::vector<int> &vec) {
  if (vec.size() < 2) {
    std::cerr << "Error: not enough elements to be sorted\n";
    std::exit(1);
  }
  std::vector<std::pair<int, int> > pairs;
  std::vector<int> sorted;

  pairs.reserve(vec.size() / 2);
  sorted.reserve(vec.size());

#ifdef DISPLAY_DEBUG_MSG
    std::cout << "\nSorting vector ...\n";
#endif
  mergeInsertionSort(vec, pairs, sorted);
}

void PmergeMe::sort(std::deque<int> &deq) {
  if (deq.size() < 2) {
    std::cerr << "Error: not enough elements to be sorted\n";
    std::exit(1);
  }
  std::deque<std::pair<int, int> > pairs;
  std::deque<int> sorted;

#ifdef DISPLAY_DEBUG_MSG
    std::cout << "\nSorting deque ...\n";
#endif
  mergeInsertionSort(deq, pairs, sorted);
}

void PmergeMe::xreserve(std::vector<std::pair<int, int> > &pairs, size_t size) {
  pairs.reserve(size);
}
void PmergeMe::xreserve(std::deque<std::pair<int, int> > &pairs, size_t size) {
  (void)pairs;
  (void)size;
}
