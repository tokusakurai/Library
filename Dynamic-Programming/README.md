# 動的計画法（DP）

## 典型的な DP 問題

- [各種ナップザック問題](Knapsack.hpp)（01 ナップザック問題、個数制限なしナップザック問題、個数制限付きナップザック問題）

- [最長共通部分列（LCS）](Longest_Common_Subsequence.hpp)

- [編集距離](Edit_Distance.hpp)

- [最長増加部分列（LIS）](Longest_Increasing_Subsequence.hpp)（DP 配列の再利用で計算量が落ちるインライン DP）

- [転倒数](Inversion_Number.hpp)

- [分割数テーブル](Partition_Number.hpp)

- [最大長方形](Largest_Rectangle.hpp)

- [スライド最小値](Slide_Min.hpp)

## 累積和

累積和を DP で前計算することによって区間和を効率的に求めることができる。

- [1 次元累積和](Cumulative_Sum_1D.hpp)

- [2 次元累積和](Cumulative_Sum_2D.hpp)

## 凸数列の (min,+) 畳み込み

2 つの凸数列に対する添え字加算・最小値畳み込み。

- [凸数列の (min,+) 畳み込み](Concave_Min_Plus_Convolution.hpp)

## Convex-Hull-Trick

直線の追加クエリ（ただし、追加する直線の傾きは単調）と、追加された直線群におけるある点での値の最小値（または最大値）クエリを扱える。

- [Convex-Hull-Trick](Convex_Hull_Trick.hpp)

## Slope-Trick

全ての点において傾きが（存在すれば）整数となるような凸関数を、傾きが変化する点の座標を管理することによって効率的に扱うことができる。

- [Slope-Trick](Slope_Trick.hpp)

## Mo のアルゴリズム

配列が静的かつ区間クエリの先読みが出来る場合、処理するクエリの順番を工夫することで効率的にクエリを処理できる。

- [Mo のアルゴリズム（雛形）](Mo_Template.hpp)

- [Mo のアルゴリズム（例）](Mo_Example.hpp)（区間内の要素の種類数を扱える）
