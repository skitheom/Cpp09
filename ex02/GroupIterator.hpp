#ifndef GROUP_ITERATOR_HPP
#define GROUP_ITERATOR_HPP

#include <algorithm>
#include <cassert>
#include <iterator>

////////////////////////////////////////////////////////////
// Class 定義
////////////////////////////////////////////////////////////

template <typename Iterator> class GroupIterator {

public:
  ////////////////////////////////////////////////////////////
  // Public types

  typedef std::random_access_iterator_tag iterator_category;
  typedef Iterator iterator_type;
  typedef typename std::iterator_traits<Iterator>::value_type value_type;
  typedef typename std::iterator_traits<Iterator>::pointer pointer;
  typedef typename std::iterator_traits<Iterator>::reference reference;
  typedef
      typename std::iterator_traits<Iterator>::difference_type difference_type;

  ////////////////////////////////////////////////////////////
  // Orthodox Canonical Form

  GroupIterator() : it_(), size_(1) {}
  GroupIterator(Iterator it, std::size_t size) : it_(it), size_(size) {}
  GroupIterator(const GroupIterator &other)
      : it_(other.it_), size_(other.size_) {};
  ~GroupIterator() {}

  GroupIterator &operator=(const GroupIterator &other) {
    if (this != &other) {
      it_ = other.it_;
      size_ = other.size_;
    }
    return *this;
  }

  ////////////////////////////////////////////////////////////
  // Members access

  // it位置のgroup左端（左端のfollower）のItを返す
  Iterator base() const { return it_; }
  // 現在のgroupのサイズを返す
  std::size_t size() const { return size_; }

  ////////////////////////////////////////////////////////////
  // Element access

  // 要素アクセス（代表値：グループの最後）
  // itがある位置のgroupの代表（右端のleader）への参照やポインタを返す
  reference operator*() const { return *(it_ + size_ - 1); }
  pointer operator->() const { return &(operator*()); }

  ////////////////////////////////////////////////////////////
  // Increment/decrement operators

  // イテレータのgroup単位での進行、後退
  GroupIterator &operator++() {
    it_ += size_;
    return *this;
  }

  GroupIterator operator++(int) {
    GroupIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  GroupIterator &operator--() {
    it_ -= size_;
    return *this;
  }

  GroupIterator operator--(int) {
    GroupIterator tmp = *this;
    --(*this);
    return tmp;
  }

  GroupIterator &operator+=(std::size_t n) {
    it_ += size_ * n;
    return *this;
  }

  GroupIterator &operator-=(std::size_t n) {
    it_ -= size_ * n;
    return *this;
  }

  ////////////////////////////////////////////////////////////
  // Elements access operators

  // pos番目のgroupの代表にアクセスする
  reference operator[](std::size_t pos) {
    return *(it_ + pos * size_ + size_ - 1);
  }

  reference operator[](std::size_t pos) const {
    return *(it_ + pos * size_ + size_ - 1);
  }

private:
  Iterator it_;      // 基底のイテレーター
  std::size_t size_; // 現在のgroupの大きさ（ex. pairなら2）
};

////////////////////////////////////////////////////////////
// Non-member functions（自由関数）
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Construction functions

// 最初の階層（単要素）をsize=1としてgroup化するときに用いる
template <typename Iterator>
GroupIterator<Iterator> makeGroupIt(Iterator it, std::size_t size) {
  return GroupIterator<Iterator>(it, size);
}

// 再帰的に深いグループ（ペアのペアの…）を作るときに、size=2として用いる
template <typename Iterator>
GroupIterator<Iterator> makeGroupIt(GroupIterator<Iterator> it,
                                    std::size_t size) {
  return GroupIterator<Iterator>(it.base(), size * it.size());
}

////////////////////////////////////////////////////////////
// Swap as group

// lhs と rhs の各 group（size 個分の要素）を一括で入れ替える
template <typename Iterator1, typename Iterator2>
void iter_swap(GroupIterator<Iterator1> lhs, GroupIterator<Iterator2> rhs) {
  std::swap_ranges(lhs.base(), lhs.base() + lhs.size(), rhs.base());
}

////////////////////////////////////////////////////////////
// Comparison operators

template <typename Iterator1, typename Iterator2>
bool operator==(const GroupIterator<Iterator1> &lhs,
                const GroupIterator<Iterator2> &rhs) {
  return lhs.base() == rhs.base();
}

template <typename Iterator1, typename Iterator2>
bool operator!=(const GroupIterator<Iterator1> &lhs,
                const GroupIterator<Iterator2> &rhs) {
  return lhs.base() != rhs.base();
}

////////////////////////////////////////////////////////////
// Relational operators

// 比較演算子：グループの先頭位置（base）をもとに比較（It位置の比較）
template <typename Iterator1, typename Iterator2>
bool operator<(const GroupIterator<Iterator1> &lhs,
               const GroupIterator<Iterator2> &rhs) {
  return lhs.base() < rhs.base();
}

template <typename Iterator1, typename Iterator2>
bool operator<=(const GroupIterator<Iterator1> &lhs,
                const GroupIterator<Iterator2> &rhs) {
  return lhs.base() <= rhs.base();
}

template <typename Iterator1, typename Iterator2>
bool operator>(const GroupIterator<Iterator1> &lhs,
               const GroupIterator<Iterator2> &rhs) {
  return lhs.base() > rhs.base();
}

template <typename Iterator1, typename Iterator2>
bool operator>=(const GroupIterator<Iterator1> &lhs,
                const GroupIterator<Iterator2> &rhs) {
  return lhs.base() >= rhs.base();
}

////////////////////////////////////////////////////////////
// Arithmetic operators

template <typename Iterator>
GroupIterator<Iterator> operator+(GroupIterator<Iterator> it, std::size_t n) {
  return it += n;
}

template <typename Iterator>
GroupIterator<Iterator> operator+(std::size_t n, GroupIterator<Iterator> it) {
  return it += n;
}

template <typename Iterator>
GroupIterator<Iterator> operator-(GroupIterator<Iterator> it, std::size_t n) {
  return it -= n;
}

template <typename Iterator>
typename GroupIterator<Iterator>::difference_type
operator-(const GroupIterator<Iterator> &lhs,
          const GroupIterator<Iterator> &rhs) {
  assert(lhs.size() == rhs.size());
  return (lhs.base() - rhs.base()) / lhs.size();
}

#endif // GROUP_ITERATOR_HPP

/**
 * GroupIteratorerator は STL コピーせずに、グループ単位での it の動きを
 * 管理して、仮想的にデータをグループ扱いするための custom iterator になる。
 *
 * size_ がグループの大きさを表すので、
 *
 * - ++演算子などで group 単位で it を移動できる
 * - *演算子で「代表値（例：最後の要素）」を取得できる
 *
 * 実際のデータは std::vector などの1本のコンテナに格納されたまま。
 * メモリのコピーなしにペア、ペアのペア…のような再帰的構造を表現できる。
 */
