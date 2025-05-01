/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:35:52 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/01 04:07:19 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include "CmpInt.hpp"
#include <cstdlib>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace Utils {

void parseInput(int size, const char **userInput, IntVec &vec) {
  vec.reserve(size);
  for (int i = 0; i < size; ++i) {
    char *endptr;
    errno = 0;
    long num = std::strtol(userInput[i], &endptr, 10);
    if (errno != 0 || num < 0 || num > std::numeric_limits<int>::max() ||
        *endptr != '\0') {
      std::ostringstream oss;
      oss << "Error: Invalid userInput: \"" << userInput[i] << "\"";
      throw std::runtime_error(oss.str());
    }
    CmpInt cmpInt(static_cast<int>(num));
    vec.push_back(cmpInt);
  }
}

double getTime(clock_t start, clock_t end) {
  return (static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC);
}

} // namespace Utils
