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

// TODO: テンプレートを使った処理の共通化

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
  mergeInsertionSort(vec);
}

void PmergeMe::sort(std::deque<int> &deq) {
  if (deq.size() < 2) {
    std::cerr << "Error: not enough elements to be sorted\n";
    std::exit(1);
  }
  mergeInsertionSort(deq);
}

void PmergeMe::mergeInsertionSort(std::vector<int> &vec) {
  const size_t size = vec.size();

  // 1.pairを作る
  std::vector<std::pair<int, int> > pairs;
  int singleElement = -1;

  if (size % 2 != 0) {
    singleElement = vec.back();
    vec.pop_back();
  }
  pairs.reserve(size / 2); // vectorにだけ必要
  buildPairs(vec, pairs);

  // 2. 各pairのうち、大きい方の値(Leaders)をMerge Sortする
  mergeSortPairs(pairs, 0, pairs.size() - 1);

  // 3. Jacobsthal数列に従いleaders & followersを挿入
  std::vector<int> sorted;
  sorted.reserve(size);
  insertJacobsthal(pairs, sorted);

  // 4.singleElementをbinaryInsertion
  if (singleElement != -1) {
    binaryInsertion(sorted, singleElement);
  }
  // 5. result を　originalのvecに入れ替える
  // 最初から、vecを初期化->書き換えるでも良かったし、
  // sortedの結果を別のvectorで返す設計でも良かったのかもしれない
  // 結局sortが同一データ構造上で起こるべきかどうかという問題ではある
  vec = sorted;
}

void PmergeMe::mergeInsertionSort(std::deque<int> &deq) {
  const size_t size = deq.size();

  // 1.pairを作る
  std::deque<std::pair<int, int> > pairs;
  int singleElement = -1;

  if (size % 2 != 0) {
    singleElement = deq.back();
    deq.pop_back();
  }
  buildPairs(deq, pairs);

  // 2. 各pairのうち、大きい方の値(Leaders)をMerge Sortする
  mergeSortPairs(pairs, 0, pairs.size() - 1);

  // 3. Jacobsthal数列に従いleaders & followersを挿入
  std::deque<int> sorted;
  insertJacobsthal(pairs, sorted);

   // 4.singleElementをbinaryInsertion
   if (singleElement != -1) {
    binaryInsertion(sorted, singleElement);
  }
  // 5. result を　originalのdequeに入れ替える
  deq = sorted;
}
