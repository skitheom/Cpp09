/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:35:52 by sakitaha          #+#    #+#             */
/*   Updated: 2025/04/30 23:25:32 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include <cstdlib>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace Utils {

void parseInput(int argc, const char **argv, IntVec &vec) {
  vec.reserve(argc - 1);
  for (int i = 1; i < argc; ++i) {
    char *endptr;
    errno = 0;
    long num = std::strtol(argv[i], &endptr, 10);
    if (errno != 0 || num < 0 || num > std::numeric_limits<int>::max() ||
        *endptr != '\0') {
      std::ostringstream oss;
      oss << "Error: Invalid input: \"" << argv[i] << "\"";
      throw std::runtime_error(oss.str());
    }
    vec.push_back(static_cast<int>(num));
  }
}

} // namespace Utils
