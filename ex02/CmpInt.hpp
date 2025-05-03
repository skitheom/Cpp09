#ifndef CMP_INT_HPP
#define CMP_INT_HPP

#include <deque>
#include <ostream>
#include <vector>

class CmpInt {
public:
  CmpInt();
  CmpInt(int value);
  CmpInt(const CmpInt &other);
  ~CmpInt();

  CmpInt &operator=(const CmpInt &other);

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

typedef std::vector<CmpInt> IntVec;
typedef IntVec::iterator IntVecIt;
typedef std::deque<CmpInt> IntDeq;
typedef IntDeq::iterator IntDeqIt;

std::ostream &operator<<(std::ostream &os, const CmpInt &obj);

#endif // CMP_INT_HPP
