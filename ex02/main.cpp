/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:33:04 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/08 15:44:04 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

/* Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us */

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Error" << std::endl;
    return 1;
  }
  PmergeMe pmergeme;
  (void)pmergeme;
  (void)argv;

  std::cout << "End" << std::endl;
  return 0;
}
