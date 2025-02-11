# CPP Module 09
42 project

## Topics
- STL

## Exercises
- 各exerciseにおいて必ずコンテナを使う
- 各課題で用いるコンテナは重複してはならない

### Exercise 00: Bitcoin Exchange
- Bitcoin交換レートのCSVを{日付, ExchangeRate}の形式に整理する
- 特定の日付（あるいはそれに最も近いlowerの日付）の値で計算する
- mapを選択

TODO: headerの中身を単に読み飛ばさずに、正しい形式かをチェックする
TODO: a float or a positive integer, between 0 and 1000 のチェック

### Exercise 01: Reverse Polish Notation
- Reverse Polish Notation は算式記法。被演算子のあとに演算子を置く
- 状態を持つ必要はない
- stackを選択

TODO: long long はc98では使えないのでは？要確認

### Exercise 02: PmergeMe
- Merge-insertion sort
- The Art of Computer Programming (TAOCP) を参照すればok

#### Merge insertion.

Merge Insertion Sort (Knuth, TAOCP vol.3)

1. pairを作る

`K1:K2, K3:K4, ..., K19:K20;`
要素数が21の場合、10個のpairに要素を分割して比較
- Leaders:   大きい値を持つ
- Followers: 小さい値を持つ

2. 各pairをLeadersの値をもとにMerge Sort

`a1->a2->a3->a4->a5->a6->a7->a8->a9->a10`
大きい方の値(leaders)をsort

3. Jacobsthal 数列に従い、小さい方の値(followers)を挿入(二分探索)

`b3`(`a3`のペア)を`{b1, a1, a2}`に挿入
次に`b2`を`a2`未満の位置に挿入

4. 適切な順序で比較する

`c1->c2->c3->c4->c5->c6->a4->a5->a6->a7->a8->a9->a10`
cはsort済みの部分（元`a1, b1, a2, b2, a3, b3`）

`a4`以降は引き続きペア`b`を持つ

`b5`を主鎖のなかの適切な位置に挿入した後で、`b4`を3つの値と比較しながらいれていく
この場合はまず`c4`,`c2`,`c6`の順に比較する

`b7`ではなく先に`b11`を主鎖に挿入する。比較対象は`b10`,`b9`,`b8`,`b7`,`b6`である

References
Knuth, D. E. (1998). Sorting and searching.

#### Jacobsthal 数列の一般項目

ヤコブスタール数列の一般項：
$J_n = \frac{2^n - (-1)^n}{3}$

```cpp
 Jacobsthal number 参考値
 初期値: prev: 0, curr: 1
 i = 0: prev: 1, curr: 1
 i = 1: prev: 1, curr: 3
 i = 2: prev: 3, curr: 5
 i = 3: prev: 5, curr: 11
 i = 4: prev: 11, curr: 21
 i = 5: prev: 21, curr: 43
 i = 6: prev: 43, curr: 85
 ```

## References

[CPP Module 09(For 42 École Students Only)](https://projects.intra.42.fr/projects/cpp-module-09)

__Exercise 00__
- [Program to check if a date is valid or not](https://www.geeksforgeeks.org/program-check-date-valid-not/)
- [How to Open and Close a File in C++?](https://www.geeksforgeeks.org/how-to-open-and-close-file-in-cpp/)
- [CSV File Management Using C++](https://www.geeksforgeeks.org/csv-file-management-using-c/)
- [std::map<Key,T,Compare,Allocator>::lower_bound](https://en.cppreference.com/w/cpp/container/map/lower_bound)

__Exercise 01__
- [逆ポーランド記法と木構造の絵](https://qiita.com/yumura_s/items/ddb0d143fb0e9a082891) ... 図があってわかりやすい解説
- [How to Split a String by a Delimiter in C++?](https://www.geeksforgeeks.org/how-to-split-string-by-delimiter-in-cpp/) ... token分割の方法について
- [Evaluate the Value of an Arithmetic Expression in Reverse Polish Notation in Java](https://www.geeksforgeeks.org/evaluate-the-value-of-an-arithmetic-expression-in-reverse-polish-notation-in-java/)
- [【C言語】算術オーバーフローと回避方法](https://hiroyukichishiro.com/arithmetic-overflow-in-c-language/) ... overflow処理
- [Reverse Polish Notation](https://mathworld.wolfram.com/ReversePolishNotation.html)

__Exercise 02__
- [Art of Computer Programming, The: Volume 3: Sorting and Searching, 2nd Edition, p.184](https://www.informit.com/store/art-of-computer-programming-volume-3-sorting-and-searching-9780201896855)
- [The Art of Computer Programming Volume 3 Sorting and Searching Second Edition 日本語版](https://www.kadokawa.co.jp/product/312356800000/)
- [CPP09 Ford–Johnson algorithm](https://medium.com/@toukmati2000/cpp09-ford-johnson-algorithm-e6ad43288d4b)
- [Measure execution time with high precision in C/C++](https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/)
c++11のchrono::high_resolution_clock::now();は使えない
- [Jacobsthal and Jacobsthal-Lucas numbers](https://www.geeksforgeeks.org/jacobsthal-and-jacobsthal-lucas-numbers/) Jacobsthalの計算方法（ver.3を使用）

## ???

- [Learning c++98 in 2024](https://www.reddit.com/r/cpp_questions/comments/1986lga/learning_c98_in_2024/)

### 複数のリモートリポジトリを設定する

#### `git remote add`
追加するラベルは、通常 origin とは別の名前を付ける
```
git remote add [任意のラベル] [新規で追加したいリモートリポジトリのアドレス]
```
Ex.
```
git remote add github git@github.com:skitheom/Cpp09.git
git remote add gitlab git@gitlab.com:skitheom/Cpp09.git
```

#### `git remote -v`
現在登録されているリモートリポジトリを確認
```
 ~/code/cppModules/Cpp09/ex01/ [main*] git remote -v
github  git@github.com:skitheom/Cpp09.git (fetch)
github  git@github.com:skitheom/Cpp09.git (push)
gitlab  git@gitlab.com:skitheom/Cpp09.git (fetch)
gitlab  git@gitlab.com:skitheom/Cpp09.git (push)
```

#### 特定のリモートへ `push`, `fetch`, `pull`

`git push [ラベル] main`

Ex.
```
git push github main   # GitHub に push
git push gitlab main   # GitLab に push

git fetch github       # GitHub の最新状態を取得
git fetch gitlab       # GitLab の最新状態を取得

git pull github main   # GitHub から `main` を pull
git pull gitlab main   # GitLab から `main` を pull
```

複数のリポジトリを設定することで、異なるリポジトリ間のコミット履歴を反映する
