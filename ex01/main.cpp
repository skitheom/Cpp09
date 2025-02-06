/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:57:30 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/06 20:20:38 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <exception>
#include <iostream>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: ./RPN \"input\"\n";
    return 1;
  }
  try {
    RPN::calculateRPN(argv[1]);
  } catch (const std::exception &e) {
    std::cout << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
