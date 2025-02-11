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

/*


int main() {
    std::vector<std::pair<int, int> > pairs; // ✅ C++98 の正しい書き方

    // std::make_pair を使ってペアを追加
    pairs.push_back(std::make_pair(3, 5));
    pairs.push_back(std::make_pair(7, 9));

    // ペアの内容を表示
    for (size_t i = 0; i < pairs.size(); ++i) {
        std::cout << "Pair " << i << ": (" << pairs[i].first << ", " <<
pairs[i].second << ")" << std::endl;
    }

    return 0;
}
*/

void PmergeMe::mergeInsertionSort(std::vector<int> &vec) {
  const size_t size = vec.size();

  // 1.pairを作る
  std::vector<std::pair<int, int> > pairs;
  std::vector<int> singleElement;

  if (size % 2 != 0) {
    singleElement.push_back(vec.back());
    vec.pop_back();
  }
  pairs.reserve(size / 2); // vectorにだけ必要
  buildPairs(vec, pairs);

  // 2. 各pairのうち、大きい方の値(Leaders)をMerge Sortする
  mergeSortPairs(pairs, 0, pairs.size() - 1);

  // 3. 最初だけ特殊で、あとはJacobsthal数列に従いfollowersを挿入
  std::vector<int> sorted;
  sorted.reserve(size);
  sorted.push_back(pairs[0].second); // secondが最小値
  // Leadersはsortedにすべていれる
  for (size_t i = 0; i < pairs.size(); ++i) {
    sorted.push_back(pairs[i].first);
  }

  // [...]
}

void PmergeMe::mergeInsertionSort(std::deque<int> &deq) {
  std::deque<std::pair<int, int> > pairs;
  std::deque<int> singleElement;

  if (deq.size() % 2 != 0) {
    singleElement.push_back(deq.back());
    deq.pop_back();
  }
  buildPairs(deq, pairs);
  // ソート処理...
}
