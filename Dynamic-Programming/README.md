# 動的計画法(DP)

## 典型的なDP問題

- [各種ナップザック問題](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Knapsack.hpp) (01ナップザック問題、個数制限なしナップザック問題、個数制限付きナップザック問題)

- [最長共通部分列(LCS)](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Longest_Common_Subsequence.hpp)

- [編集距離](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Edit_Distance.hpp)

- [最長増加部分列(LIS)](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Longest_Increasing_Subsequence.hpp) (DP配列の再利用で計算量が落ちるインラインDP)

- [転倒数](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Inversion_Number.hpp)

- [分割数テーブル](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Partition_Number.hpp)

- [最大長方形](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Largest_Rectangle.hpp)

- [スライド最小値](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Slide_Min.hpp)

## 累積和
累積和をDPで前計算することによって区間和を効率的に求めることができる。

- [1次元累積和](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Cumulative_Sum_1D.hpp)

- [2次元累積和](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Cumulative_Sum_2D.hpp)

## 高速ゼータ・メビウス・アダマール変換
長さが2べきであるような配列に対する各種の変換。応用としてAND・OR・XOR畳み込みやsubset畳み込みがある。

- [高速ゼータ・メビウス・アダマール変換](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Zeta_Mobius_Hadamard.hpp)

- [ビット演算による添字畳み込み](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Bitwise_Convolution.hpp) (AND・OR・XOR畳み込み、subset畳み込み)

## Convex-Hull-Trick
直線の追加クエリ(ただし、追加する直線の傾きは単調)と、追加された直線群におけるある点での値の最小値(または最大値)クエリを扱える。

- [Convex-Hull-Trick](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Convex_Hull_Trick.hpp)

## Moのアルゴリズム
配列が静的かつ区間クエリの先読みが出来る場合、処理するクエリの順番を工夫することで効率的にクエリを処理できる。

- [Moのアルゴリズム(雛形)](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Mo_Template.hpp)

- [Moのアルゴリズム(例)](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Mo_Example.hpp) (区間内の要素の種類数を扱える)
