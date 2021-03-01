# 動的計画法(DP)

## 典型的なDP問題

- [各種ナップザック問題](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Knapsack.cpp) (01ナップザック問題、個数制限なしナップザック問題、個数制限付きナップザック問題)

- [最長共通部分列(LCS)](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/LCS.cpp)

- [編集距離](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Edit_Distance.cpp)

- [最長増加部分列(LIS)](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/LIS.cpp) (DP配列の再利用で計算量が落ちるインラインDP)

- [分割数テーブル](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Partition_Number.cpp)

- [最大長方形](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Largest_Rectangle.cpp)

- [スライド最小値](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Slide_Min.cpp)

## 高速ゼータ・メビウス・アダマール変換
長さが2べきであるような配列に対する各種の変換。応用としてAND・OR・XOR畳み込みがある。

- [高速ゼータ・メビウス・アダマール変換](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Zeta_Mobius_Hadamard.cpp)

## Convex-Hull-Trick
直線の追加クエリ(ただし、追加する直線の傾きは単調)と、追加された直線群におけるある点での値の最小値(または最大値)クエリを扱える。

- [Convex-Hull-Trick](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Convex_Hull_Trick.cpp)

## Moのアルゴリズム
配列が静的かつ区間クエリの先読みが出来る場合、処理するクエリの順番を工夫することで効率的にクエリを処理できる。

- [Moのアルゴリズム(雛形)](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Mo_Template.cpp)

- [Moのアルゴリズム(例)](https://github.com/tokusakurai/Library/blob/main/Dynamic-Programming/Mo_Example.cpp) (区間内の要素の種類数を扱える)
