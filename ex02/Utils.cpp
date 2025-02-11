/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:35:52 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/12 02:31:53 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include <sstream>
#include <stdexcept>

Utils::Utils() {}

Utils::Utils(const Utils &other) { (void)other; }

Utils::~Utils() {}

Utils &Utils::operator=(const Utils &other) {
  (void)other;
  return *this;
}

void Utils::parseInput(int argc, const char **argv, std::vector<int> &vec) {
  vec.reserve(argc - 1);
  for (int i = 1; i < argc; ++i) {
    char *endptr;
    errno = 0;
    long num = std::strtol(argv[i], &endptr, 10);
    if (errno != 0 || num < 0 || num > INT_MAX || *endptr != '\0') {
      std::ostringstream oss;
      oss << "Error: Invalid input: \"" << argv[i] << "\"";
      throw std::runtime_error(oss.str());
    }
    vec.push_back(static_cast<int>(num));
  }
}
