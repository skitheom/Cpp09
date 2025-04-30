/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:34:07 by sakitaha          #+#    #+#             */
/*   Updated: 2025/04/30 23:29:48 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <cerrno>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

// 型定義
typedef std::vector<int> IntVec;
typedef std::deque<int> IntDeq;
typedef std::vector<std::pair<int, int> > IntPairVec;
typedef std::deque<std::pair<int, int> > IntPairDeq;

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
}

#endif // UTILS_HPP
