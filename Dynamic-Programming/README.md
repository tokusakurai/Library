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

## 凸数列の(min,+)畳み込み
2つの凸数列に対する添え字加算・最小値畳み込み。

- [凸数列の(min,+)畳み込み](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Concave_Min_Plus_Convolution.hpp)

## Convex-Hull-Trick
直線の追加クエリ(ただし、追加する直線の傾きは単調)と、追加された直線群におけるある点での値の最小値(または最大値)クエリを扱える。

- [Convex-Hull-Trick](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Convex_Hull_Trick.hpp)

## Slope-Trick
全ての点において傾きが(存在すれば)整数となるような凸関数を、傾きが変化する点の座標を管理することによって効率的に扱うことができる。

- [Slope-Trick](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Slope_Trick.hpp)

## Moのアルゴリズム
配列が静的かつ区間クエリの先読みが出来る場合、処理するクエリの順番を工夫することで効率的にクエリを処理できる。

- [Moのアルゴリズム(雛形)](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Mo_Template.hpp)

- [Moのアルゴリズム(例)](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Mo_Example.hpp) (区間内の要素の種類数を扱える)
