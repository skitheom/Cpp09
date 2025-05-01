/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmpInt.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 02:52:49 by sakitaha          #+#    #+#             */
/*   Updated: 2025/05/01 04:14:53 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmpInt.hpp"

int CmpInt::cmpCount_ = 0;

CmpInt::CmpInt() : value_(-1) {}

CmpInt::CmpInt(int value) : value_(value) {}

CmpInt::CmpInt(const CmpInt &other) : value_(other.value_) {}

CmpInt::~CmpInt() {}

CmpInt &CmpInt::operator=(const CmpInt &other) {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

bool CmpInt::operator<(const CmpInt &rhs) const {
  ++cmpCount_;
  return value_ < rhs.value_;
}

bool CmpInt::operator<=(const CmpInt &rhs) const {
  ++cmpCount_;
  return value_ <= rhs.value_;
}

bool CmpInt::operator>(const CmpInt &rhs) const {
  ++cmpCount_;
  return value_ > rhs.value_;
}

bool CmpInt::operator>=(const CmpInt &rhs) const {
  ++cmpCount_;
  return value_ >= rhs.value_;
}

bool CmpInt::operator==(const CmpInt &rhs) const {
  ++cmpCount_;
  return value_ == rhs.value_;
}

bool CmpInt::operator!=(const CmpInt &rhs) const {
  ++cmpCount_;
  return value_ != rhs.value_;
}

int CmpInt::getValue() const { return value_; }

void CmpInt::resetComparisons() { cmpCount_ = 0; }

int CmpInt::getComparisonCount() { return cmpCount_; }

std::ostream &operator<<(std::ostream &os, const CmpInt &obj) {
  return os << obj.getValue();
}
