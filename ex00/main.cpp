/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:53:10 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/03 23:50:59 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <exception>
#include <iostream>

int main(int argc, const char *argv[]) {
#ifdef DISPLAY_DEBUG_MSG
  std::cerr << "[Debug Mode] " << std::endl;
#endif
  if (argc != 2) {
    std::cerr << "Error: could not open file." << std::endl;
    return 1;
  }
  try {
    BitcoinExchange bce;
    bce.processInput(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
