/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:26:45 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/03 05:21:28 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Log.hpp"
#include "CmpInt.hpp"
#include <iostream>

namespace Log {

void log(const std::string &msg) {
#ifdef DISPLAY_DEBUG_MSG
  std::cout << msg << std::endl;
#endif
  (void)msg;
}

void log(const std::string &msg, int value) {
#ifdef DISPLAY_DEBUG_MSG
  std::cout << msg << ": " << value << std::endl;
#endif
  (void)msg;
  (void)value;
}

void log(const std::string &msg, size_t value) {
  #ifdef DISPLAY_DEBUG_MSG
    std::cout << msg << ": " << value << std::endl;
  #endif
    (void)msg;
    (void)value;
  }

void log(const std::string &msg, CmpInt &cmpInt) {
#ifdef DISPLAY_DEBUG_MSG
  std::cout << msg << ": " << cmpInt << std::endl;
#endif
  (void)msg;
  (void)cmpInt;
}

} // namespace Log
