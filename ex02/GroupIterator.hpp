#ifndef GROUP_ITERATOR_HPP
#define GROUP_ITERATOR_HPP

#include <iterator>

template <typename Iterator> class GroupIterator {

public:
  ////////////////////////////////////////////////////////////
  // Public types

  // random_access_iteratorと明示 配列のように+, -, [] などの操作ができる
  using iterator_category = std::random_access_iterator_tag;
  // iterator_type という型名は、Iterator を指す
  using iterator_type = Iterator;
  // Iterator が指している要素の型を value_type とする
  using value_type = typename std::iterator_traits<Iterator>::value_type;
  // Iterator が返すポインタ型（使わないかもしれない）
  using pointer = typename std::iterator_traits<Iterator>::pointer;
  // Iterator が返す参照型 (int& あるいは *It)
  using reference = typename std::iterator_traits<Iterator>::reference;
  // 2つの Iterator の距離を表す型
  using difference_type =
      typename std::iterator_traits<Iterator>::difference_type;

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

  Iterator base() const { return it_; }
  std::size_t size() const { return size_; }

  ////////////////////////////////////////////////////////////
  // Element access

  // 要素アクセス（代表値：グループの最後）
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
  // TODO: operator+= や operator-= なども実装してもいいかも

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
