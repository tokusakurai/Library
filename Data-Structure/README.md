# データ構造

## Union-Find木
2つの集合を統合して1つにすること(Union)と、ある要素が属する集合を求めること(Find)ができる。

- [Union-Find木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Union_Find_Tree.hpp)

- [重み付きUnion-Find木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Weighted_Union_Find_Tree.hpp) (各頂点に重みを与えたとき、weight(y)-weight(x) = wの制約を扱える)

- [部分永続Union-Find木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Partitially_Persistent_Union_Find_Tree.hpp) (各Union操作に時刻を与えたとき、任意の時刻でのFindクエリを扱える)

- [Undo可能Union-Find木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Undo_Union_Find_Tree.hpp) (Union操作を巻き戻すことができる)

## Binary-Indexed木
配列に対して1点加算と区間和取得ができる。セグメント木と比べてメモリや計算量の定数倍が軽いというメリットがある。

- [Binary-Indexed木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Binary_Indexed_Tree.hpp)

## セグメント木
配列に対して1点更新と区間演算ができる。ただし、二項演算はモノイドとしての性質を満たさなければならない。

- [セグメント木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Segment_Tree.hpp)

遅延評価(必要になるまで更新を保留すること)を用いることによって、区間更新を扱うこともできる。

- [双対セグメント木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Dual_Segment_Tree.hpp) (作用素の二項演算がモノイドの性質を満たすとき、区間更新と1点取得を扱える)

- [遅延評価付きセグメント木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Lazy_Segment_Tree.hpp) (上記2つを組み合わせることで区間更新と区間演算を扱える)

セグメント木にセグメント木を乗せることで、1点更新と矩形演算を扱うこともできる。

- [2次元セグメント木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Segment_Tree_2D.hpp)

## スパーステーブル
配列が静的かつ二項演算が結合則と冪等性を満たすとき、区間演算ができる。セグメント木と比べてクエリ計算量は小さいが、メモリ消費が大きいことと扱える演算の幅が小さくなることに注意。

- [スパーステーブル](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Sparse_Table.hpp)

## 平方分割
配列を適当なサイズごとのバケットに分割して区間クエリを処理するテクニック。セグメント木と比べて計算量は落ちるが、扱えるクエリの幅が大きい。

- [平方分割(雛形)](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Sqrt_Decomposition_Template.hpp)

- [平方分割(例)](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Sqrt_Decomposition_Example.hpp) (区間chmin、区間chmax、区間add、区間sumクエリを扱える)

## 二分探索木
- [スプレー木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Splay_Tree.hpp) (スプレー操作を行うことで平衡を保つ二分木)
