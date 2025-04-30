/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:26:45 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/01 00:00:42 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Log.hpp"
#include <iostream>

namespace Log {

void log(const std::string &msg) {
#ifdef DISPLAY_DEBUG_MSG
  std::cout << msg << std::endl;
#endif
}

void log(const std::string &msg, int value) {
#ifdef DISPLAY_DEBUG_MSG
  std::cout << msg << ": " << value << std::endl;
#endif
}

} // namespace Log
