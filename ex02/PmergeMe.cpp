/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:33:08 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/10 15:25:50 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
  if (this != &other) {
  }
  return *this;
}

void PmergeMe::sort(std::vector<int> &vec) { (void)vec; }

void PmergeMe::sort(std::deque<int> &deq) { (void)deq; }

void PmergeMe::mergeInsertionSort(std::vector<int> &vec) { (void)vec; }

void PmergeMe::mergeInsertionSort(std::deque<int> &deq) { (void)deq; }

// TODO: テンプレートを使った処理の共通化
