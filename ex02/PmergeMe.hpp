/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:33:10 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/10 15:24:09 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>

class PmergeMe {
public:
  static void sort(std::vector<int> &vec);
  static void sort(std::deque<int> &deq);

private:
  PmergeMe();
  PmergeMe(const PmergeMe &other);
  ~PmergeMe();

  PmergeMe &operator=(const PmergeMe &other);

  static void mergeInsertionSort(std::vector<int> &vec);
  static void mergeInsertionSort(std::deque<int> &deq);
};

#endif // PMERGEME_HPP
