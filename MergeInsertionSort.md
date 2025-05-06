CPP Module 09 - Exercise 02: PmergeMe

概要

本課題では、Ford–Johnson アルゴリズム（Merge-Insertion Sort） を用いて、
STLの std::vector と std::deque に対して最小の比較回数を目指すソートを実装する

背景
Merge-Insertion Sort は、比較回数を最小限に抑えることを目的としたソートアルゴリズム
テニスのトーナメントについての論文で考えられた手法
理論的な下限（情報理論的下限）は、$S(n) \geq \log_2(n!)$（Stirlingの近似によって $\Theta(n \log n)$ に収束）


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
