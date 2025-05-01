/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:34:07 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/01 04:09:32 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "CmpInt.hpp"
#include <cerrno>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

// 型定義
typedef std::vector<CmpInt> IntVec;
typedef std::deque<CmpInt> IntDeq;
typedef std::pair<CmpInt, CmpInt> IntPair;
typedef std::vector<IntPair> IntPairVec;
typedef std::deque<IntPair> IntPairDeq;

// イテレータ定義
typedef IntVec::iterator IntVecIt;
typedef IntVec::const_iterator ConstIntVecIt;
typedef IntDeq::iterator IntDeqIt;
typedef IntDeq::const_iterator ConstIntDeqIt;
typedef IntPairVec::iterator IntPairVecIt;
typedef IntPairVec::const_iterator ConstIntPairVecIt;
typedef IntPairDeq::iterator IntPairDeqIt;
typedef IntPairDeq::const_iterator ConstIntPairDeqIt;

namespace Utils {
void parseInput(int argc, const char **argv, IntVec &vec);
double getTime(clock_t start, clock_t end);
} // namespace Utils

#endif // UTILS_HPP
