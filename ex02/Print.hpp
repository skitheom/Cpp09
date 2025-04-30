/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Print.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:35:37 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/01 00:02:35 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Print.hpp
#ifndef PRINT_HPP
#define PRINT_HPP

#include "Utils.hpp"
#include <iostream>
#include <string>

namespace Print {
template <typename T> void printContainer(const std::string &msg, const T &t) {

  std::cout << msg;
  size_t count = 0;
  for (typename T::const_iterator it = t.begin(); it != t.end(); ++it) {
#ifdef MUTE_DEBUG_PRINT
    ++count;
    if (count > 10) {
      std::cout << " [...]\n";
      return;
    }
#endif
    std::cout << " " << *it;
  }
  (void)count;
  std::cout << std::endl;
}

template <typename T> void printPairs(const std::string &msg, const T &t) {

  std::cout << msg;
  for (typename T::const_iterator it = t.begin(); it != t.end(); ++it) {
    std::cout << " (" << it->first << ":" << it->second << ")";
  }
  std::cout << std::endl;
}
} // namespace Print

#endif // PRINT_HPP
