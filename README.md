# CPP Module 09
42 project

このREADMEは整理中で未完成です

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

## Ford–Johnson アルゴリズム（Merge-Insertion Sort）について

### 概要

ex02 では、Ford–Johnson アルゴリズム（Merge-Insertion Sort）を用いて、最小の比較回数を目指すソートを実装する。

Merge-Insertion Sort は、比較回数を極力抑えることを目的としたソートアルゴリズム。
もともとはテニスのトーナメント構造に関する論文で導かれた手法

### 理論

編集中

### アルゴリズムの構成（Knuth TAOCP Vol.3 §5.3.1 参照）

#### 1. pairを作る

`K1:K2, K3:K4, ..., K19:K20;`
- 入力列を2つずつのペアに分け、それぞれのペアで大小を比較する
- 各ペア内の大きい要素（仮に *leader* と呼ぶ）を抜き出して部分列とする
- 小さい要素（*follower*）は、あとで主鎖に挿入するために保存しておく
- 奇数個の入力の場合、最後の要素はペアを持たず、余剰要素として単独で残る

#### 2. Leader列への再帰的 Merge-Insertion Sort

- leader だけで構成された部分列に対して、再帰的に Merge-Insertion Sort を適用する
- 各ステップで再びペアを作り、leader の列を更新していく
- 最終的に、ソート済みの leader 列が **主鎖（main chain）** となる

#### 3. Follower の挿入　（Jacobsthal 数列に基づく）

- 主鎖が構成されたら、follower を順番に主鎖へ挿入する
- 最初の follower（b1）は対応する leader の前に無条件で挿入される
- 残りの follower たちは、**Jacobsthal 数列**に従った順序で、主鎖に対して二分探索で挿入される
- この数列は、二分探索における効率的な比較順序を導くために用いられる

### 実例

#### pairing

以下の21個の数字をソートするとする

[11 21 13 1 2 17 12 3 4 20 5 15 6 18 7 14 10 19 9 16 8]

まず、10個のpairができる
各ペアのうち、より大きな要素を（代表）をleadersとし、より小さな要素（従属）をfollowersとする

`K1:K2, K3:K4, ..., K10:K20`

ここでは昇順にソートしたいので、ペアの左側をfollower/ペアの右側をleaderにしている
Leader列に対する再帰的な呼び出しが起こり、これ以上ペアを作れない段階までペア化が進む
ペアのペアのペア...とメタペアを作る感じになる
(a : b) は a が follower、b が leader を意味する（常に b > a）

---
__Level: 0, Pair数: 10__

与えられた数列:
```c
[11 21 13 1 2 17 12 3 4 20 5 15 6 18 7 14 10 19 9 16 8]
```

pair化:
```c
(11:21), (1:13), (2:17), (3:12), (4:20), (5:15), (6:18), (7:14), (10:19), (9:16) ... 8
```
余剰要素:
```c
8
```
---
__Level: 1,  Pair数: 5__

前層のLeader列（pairの右側要素）:
```c
[21 13 17 12 20 15 18 14 19 16]
```

pair化:
```c
(13:21), (12:17), (15:20), (14:18), (16:19)
```

全体:
```c
[(1:13):(11:21)], [(3:12):(2:17)], [(5:15):(4:20)], [(7:14):(6:18)], [(9:16):(10:19)]
```
---
__Level: 2, Pair数: 2__

前層のLeader列（pairの右側要素）:
```c
[21 17 20 18 19]
```

pair化:
```c
(17:21), (18:20) ... 19
```
余剰要素:
```c
[(9:16):(10:19)]
```

全体:
```c
{[(3:12):(2:17)]:[(1:13):(11:21)]}, {[(7:14):(6:18)]:[(5:15):(4:20)]}
```
---
__Level: 3 Pair数: 1__

前層のLeader列（pairの右側要素）:
```c
[21, 20]
```

pair化:
```c
(20:21)
```

全体:
```c
<{[(7:14):(6:18)]:[(5:15):(4:20)]}:{[(3:12):(2:17)]:[(1:13):(11:21)]}>
```
---
__Level:4, Group Size: 32, Pair数:0__

前層のLeader列（pairの右側要素）:
```c
[21]
```

これ以上はpair化できないため、pairing終了

---
#### Insertion

これ以上のpairingができない段階で、Leaderによって構成された主鎖（main chain）にFollower（各ペアの小さい方の要素）および最後に残った余剰要素を、Jacobsthal 数列に基づいた順序で、**二分探索によって**挿入する

---
__Level: 4, Pair数：　0__

pairのないレベルのため、insertionもない

---
__Level: 3, Pair数: 1__

pair構成
```c
(20:21)
```

先頭のpairはすでに`follower-leader`関係としてsort済み

全体
```c
<{[(7:14):(6:18)]:[(5:15):(4:20)]}:{[(3:12):(2:17)]:[(1:13):(11:21)]}>
```
---
__Level: 2, Pair数: 2__

pair構成
```c
(18:20), (17:21) ... 余剰要素 (19)
```

図:
```c
a_1 - a_2
 |     |
b_1   b_2 ... b_3 (余剰要素)
```

sort済みの {b_1, a_1, a_2} に対し`b_3`,`b_2`を挿入する

主鎖:
```c
{18 20 21}
```

Jacobsthal数=3の時:

`a_3`の要素はないため、これがこのlevelの最後のinsertionになる
そのため、まず余剰要素の`b_3`を挿入する

`b_3`が主鎖のどの部分に入ったとしても、`b_2`は主鎖の最終要素より小さいため
同じ探索範囲（前から3要素）を維持して`b_2`を挿入する

```c
{18 20 21} <- b_3: 19
{18 19 20 | 21} <- b_2: 17
{17 18 19 20 21}
```

全体:
```c
{[(3:12):(2:17)], [(7:14):(6:18)], [(9:16):(10:19)], [(5:15):(4:20)], [(1:13):(11:21)]}
```
---
__Level: 1, Pair数: 5__
pair構成:
```c
(12:17), (14:18), (16:19), (15:20), (13:21)
```

図:
```c
a_1 - a_2 - a_3 - a_4 - a_5
 |     |     |     |     |
b_1   b_2   b_3   b_4   b_5
```

{b_1, a_1, a_2, a_3, a_4, a_5} の主鎖に
b_3 -> b_2 -> b_5 -> b_4 の順番でfollowerを挿入

主鎖:
```c
{12 17 18 19 20 21}
```

Jacobsthal数=3の時:

b_3の要素がa_3の後ろに入ることはないので、探索範囲は前から3要素
b_3がどこに挿入されても、a_2は常にa_3より小さいので
前から3要素という探索範囲は維持して挿入できる

```c
{12 17 18 | 19 20 21} <- b_3: 16
{12 16 17 | 18 19 20 21} <- b_2: 14
```

Jacobsthal数=5の時:

同様に、b_5を先に挿入し、同じ探索要素数を維持して次にb_4を挿入

```c
{12 14 16 17 18 19 20 | 21} <- b_5: 13
{12 13 14 16 17 18 19 | 20 21} <- b_4: 15
```

全体:
```c
[(3:12), (1:13), (7:14), (5:15), (9:16), (2:17), (6:18) (10:19), (4:20), (11:21)]
```
---
__Level: 0,  Pair数: 10__

pair構成:
```c
(3:12), (1:13), (7:14), (5:15), (9:16), (2:17), (6:18), (10:19), (4:20), (11:21) ... 余剰要素(8)
```

図:
```c
a_1 - a_2 - a_3 - a_4 - a_5 - a_6 - a_7 - a_8 - a_9 - a_10
 |     |     |     |     |     |     |     |     |     |
b_1   b_2   b_3   b_4   b_5   b_6   b_7   b_8   b_9   b_10 ... b_11
```

`b_1` が最小のfollowerであるため、主鎖は`b_1`+leadersから成る
{b_1, a_1, a_2, ..., a_n}
前述のようにJacobsthal数番目のfollower要素をいれて、逆順でfollowerを入れるプロセスを行う

Jacobsthal数=3の時:
`b_3` -> `b_2`

Jacobsthal数=5の時:
`b_5` -> `b_4`

Jacobsthal数=11の時:
`b_11` -> `b_10` -> `b_9` -> `b_8` -> `b_7` -> `b_6`

---
#### 結果
全体の要素数が21の時、Merge Insertion sort を使用することで
10 + S(10) + 2 + 2 + 3 + 3 + 4 + 4 + 4 + 4 + 4 = 66 steps
でsortすることができる

Merge Insertion sortは比較回数を最小化し、理論限界に非常に近い性能を発揮する
ただし通常CSにおいて比較コストは大きくないので、プログラミングでは用いられない

⸻

理論（未整理）


比較木と比較回数の理論的最小。より少ない比較回数を目指すMerge insertion sortについて

#### 5.3.1. Minumum-Comparison Sorting (Knuth, TAOCP vol.3)　より

理論的な下限（情報理論的下限）は、 $S(n) \geq \log_2(n!)$ （Stirlingの近似によって $\Theta(n \log n)$ に収束）


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

__理論的下限, Binary Insertion Sort, Straight Two-Way Merginの比較__
Binary Insertion Sort も Straight Two-Way Merging も、必ずしも理論的な最小比較回数（情報理論的下限）には到達しない

Lester Ford, Jr. と Selmer Johnson によって考案された Merge Insertion Sort は、より理論的下限に近い比較回数 でソートを行うことを目指したアルゴリズム


## References　（未整理）

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

https://codereview.stackexchange.com/questions/116367/ford-johnson-merge-insertion-sort
https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91
https://www.jstor.org/stable/2308750


- Donald E. Knuth, *The Art of Computer Programming, Volume 3: Sorting and Searching*, §5.3.1.
- Lester R. Ford, Jr. & Selmer M. Johnson, *A Tournament Problem*, 1959.

	•	Knuth, D. E. (1998). The Art of Computer Programming, Vol. 3: Sorting and Searching.
	•	Ford, L. R., & Johnson, S. M. (1959). A tournament problem.
