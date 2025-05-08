# CPP Module 09
42 project

## Topics
- STL

## Exercises
- 各exerciseにおいて必ずコンテナを使う
- 各課題で用いるコンテナは重複してはならない

### Exercise 00: Bitcoin Exchange
- Bitcoin交換レートのCSVを{日付, ExchangeRate}の形式に整理する
- 当該の日付（あるいは直近の過去の日付）の値で計算する
- std::map<time_t, double>

### Exercise 01: Reverse Polish Notation
- Reverse Polish Notation は算式記法。被演算子のあとに演算子を置く
- () や 小数を受け取る必要はなく、`0-9` の整数を扱う（結果は小数になり得る）
- std::stack<double>


### Exercise 02: PmergeMe
- Merge-insertion sort を実装する
- The Art of Computer Programming (TAOCP) 5.3.1 Merge insertion. 参照
- 比較回数を数えるため、int型をwrapperするクラス`CmpInt`を用意
- std::vector<CmpInt>, std::deque<CmpInt>

## Ford–Johnson アルゴリズム（Merge-Insertion Sort） について

### 概要

ex.02 では、Merge-Insertion Sort を用いて、最小の比較回数を目指すソートを実装する

### 背景
Merge-Insertion Sort は、比較回数を最小限に抑えることを目的としたソートアルゴリズム。テニスのトーナメントについての論文で考えられた手法
理論的な下限（情報理論的下限）は、 $S(n) \geq \log_2(n!)$ （Stirlingの近似によって $\Theta(n \log n)$ に収束）


アルゴリズムの構成（Knuth TAOCP Vol.3 §5.3.1 参照）

1. ペアの生成とリーダー・フォロワーの分離
	- 入力を2つずつペアに分け、それぞれの中で大小を比較
	- 大きい方をリーダー（leader）、小さい方をフォロワー（follower）として分類
	- これにより、リーダーだけで構成される部分列ができる

2. リーダー列に対して再帰的にMerge-Insertion Sort
	- リーダー列は再帰的にこの手法でソートされる
	- 最終的にこのリーダー列が「主鎖（main chain）」になる

3. フォロワーの挿入（Jacobsthal数列に基づく）
	- フォロワーたちは、対応するリーダーの位置を目安にして主鎖に二分探索で挿入される
	- この時、挿入の順序はJacobsthal数列に基づくことで、最適な比較範囲が得られる

Jacobsthal数列:
$J_n = \frac{2^n - (-1)^n}{3}$

例: 1, 3, 5, 11, 21, 43, …

⸻

特徴と利点
	•	比較回数を最小化することで、理論限界に非常に近い性能を発揮。
	•	ただし、実装は通常の Merge Sort や Insertion Sort よりも複雑。

⸻

補足：他のソートとの比較

アルゴリズム	最悪計算量	比較回数
Merge Sort	O(n log n)	多め
Insertion Sort	O(n²)	少数では速い
Merge-Insertion Sort	O(n log n)	比較回数は最小に近い



⸻

参考文献
	•	Knuth, D. E. (1998). The Art of Computer Programming, Vol. 3: Sorting and Searching.
	•	Ford, L. R., & Johnson, S. M. (1959). A tournament problem.

比較木と比較回数の理論的最小。より少ない比較回数を目指すMerge insertion sortについて

#### 5.3.1. Minumum-Comparison Sorting (Knuth, TAOCP vol.3)　より


#### The best worst case.
__比較木 （comparison tree）__
- 内部ノード: 比較
- 外部ノード: permutation（順列）

__最小の比較回数 （the worst case）__
- $S(n)$: n個の要素をソートするのに必要な最小の比較回数
- $2^k$: 深さ$k$の比較木は、最大で$2^k$の外部ノードを持つ
- $S(n) = k$: 比較木の深さ $k$ 最悪のケースにおける最大の深さ（比較回数）

__$n! <= 2^{S(n)}$__
- $n!$: すべての順列の数
- $2^{S(n)}$: 比較木の外部ノードの最大数
最小の比較回数$S(n)$により、permutationは最大で$2^{S(n)}$.
$n!$ 個の順列を区別するためには、比較木の外部ノードが少なくとも $n!$ 個以上要る

よって、$S(n) \geq \log_2 (n!)$
ソートアルゴリズムの最適な比較回数の理論的な下限（lower bound）を計算する

__最小の比較回数（情報理論的下限）__
the information-theoretic lower bound
- $S(n) \geq \log_2 (n!)$

__Stirlingの近似__
- $n! \approx \sqrt{2\pi n} \left( \frac{n}{e} \right)^n$ (Stirlingの公式)
- $\ln(n!) \approx n\ln n - n + \frac{1}{2} \ln n + O(1)$ 対数を取る
- $\log_2(n!) = \frac{\ln(n!)}{\ln 2} \approx \frac{n\ln n - n + \frac{1}{2} \ln n + O(1)}{\ln 2}$ 両辺を$\log_2$
- $\log_2(n!) \approx n \log_2 n - \frac{n}{\ln 2} + \frac{1}{2} \log_2 n + O(1)$ ここで分母を展開（$\ln 2$は0.693）

よって、比較木の最小比較回数の近似は
- $S(n) \geq n \log_2 n - \frac{n}{\ln 2} + \frac{1}{2} \log_2 n + O(1)$

__$S(n) = Θ(n log n)$__
Binary Insertion Sort, Tree Selection Sort, Straight Two-Way Mergingどれも最悪の場合に $\Theta(n \log n)$ の比較回数に収束。そのため情報理論的下限（最小の比較回数）と、ソートアルゴリズムの比較回数は一致する。どんな比較ソートアルゴリズムも $O (n \log n)$ より高速にはなれない

__理論的下限, Binary Insertion Sort, Straight Two-Way Merginの比較___
Binary Insertion Sort も Straight Two-Way Merging も、必ずしも理論的な最小比較回数（情報理論的下限）には到達しない

Lester Ford, Jr. と Selmer Johnson によって考案された Merge Insertion Sort は、より理論的下限に近い比較回数 でソートを行うことを目指したアルゴリズムで、 Merge Sort の分割統治 と Insertion Sort の適応的な挿入 を組み合わせ、従来のソートアルゴリズムより比較回数を削ずれる

### Merge insertion について

1. pairを作る

`K1:K2, K3:K4, ..., K19:K20;`
要素数が21の場合、10個のpairに要素を分割して比較
- Leaders:   大きい値を持つ
- Followers: 小さい値を持つ

2. 各pairをLeadersの値をもとにMerge Insertion Sort

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
- [Merge Sort – Data Structure and Algorithms Tutorials](https://www.geeksforgeeks.org/merge-sort/)

## ???

- [Learning c++98 in 2024](https://www.reddit.com/r/cpp_questions/comments/1986lga/learning_c98_in_2024/)






https://codereview.stackexchange.com/questions/116367/ford-johnson-merge-insertion-sort


https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91

https://www.jstor.org/stable/2308750
