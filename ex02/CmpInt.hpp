/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmpInt.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 02:52:20 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/01 04:14:32 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMP_INT_HPP
#define CMP_INT_HPP

#include <ostream>

class CmpInt {
public:
  CmpInt();
  CmpInt(int value);
  CmpInt(const CmpInt &other);
  ~CmpInt();

  CmpInt &operator=(const CmpInt &other);

  // 比較演算子オーバーロード
  bool operator<(const CmpInt &rhs) const;
  bool operator<=(const CmpInt &rhs) const;
  bool operator>(const CmpInt &rhs) const;
  bool operator>=(const CmpInt &rhs) const;
  bool operator==(const CmpInt &rhs) const;
  bool operator!=(const CmpInt &rhs) const;

  int getValue() const;

  static void resetComparisons();
  static int getComparisonCount();

private:
  int value_;
  static int cmpCount_;
};

std::ostream &operator<<(std::ostream &os, const CmpInt &obj);

#endif // CMP_INT_HPP
