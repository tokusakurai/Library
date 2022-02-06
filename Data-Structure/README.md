# データ構造

## Union-Find Tree

2 つの集合を統合して 1 つにすること（Union）と、ある要素が属する集合を求めること（Find）ができる。

- [Union-Find Tree](Union_Find_Tree.hpp)

- [重み付き Union-Find Tree](Weighted_Union_Find_Tree.hpp)（各頂点に重みを与えたとき、weight(y) - weight(x) = w の制約を扱える）

- [部分永続 Union-Find Tree](Partitially_Persistent_Union_Find_Tree.hpp)（各 Union 操作に時刻を与えたとき、任意の時刻での Find クエリを扱える）

- [Undo 可能 Union-Find Tree](Undo_Union_Find_Tree.hpp)（Union 操作を巻き戻すことができる）

## Binary Indexed Tree

配列に対して 1 点加算と区間和取得ができる。Segment Tree と比べてメモリや計算量の定数倍が軽いというメリットがある。

- [Binary Indexed Tree](Binary_Indexed_Tree.hpp)

## Segment Tree

配列に対して 1 点更新と区間演算ができる。ただし、二項演算はモノイドとしての性質を満たさなければならない。

- [Segment Tree](Segment_Tree.hpp)

遅延評価（必要になるまで更新を保留すること）を用いることによって、区間更新を扱うこともできる。

- [双対 Segment Tree](Dual_Segment_Tree.hpp)（作用素の二項演算がモノイドの性質を満たすとき、区間更新と 1 点取得を扱える）

- [遅延評価付き Segment Tree](Lazy_Segment_Tree.hpp)（上記 2 つを組み合わせることで区間更新と区間演算を扱える）

- [Segment Tree Beats](Segment_Tree_Beats.hpp)（区間 chmin・chmax を扱える）

Segment Tree に Segment Tree や双対 Segment Tree を乗せることで、2 次元平面上の 1 点更新と矩形演算や矩形更新と 1 点取得を扱うこともできる。

- [2 次元 Segment Tree](Segment_Tree_2D.hpp)

- [2 次元双対 Segment Tree](Dual_Segment_Tree_2D.hpp)

## スパーステーブル

配列が静的かつ二項演算が結合則と冪等性を満たすとき、区間演算ができる。Segment Tree と比べてクエリ計算量は小さいが、メモリ消費が大きいことと扱える演算の幅が小さくなることに注意。

- [スパーステーブル](Sparse_Table.hpp)

## 平方分割

配列を適当なサイズごとのバケットに分割して区間クエリを処理するテクニック。Segment Tree と比べて計算量は落ちるが、扱えるクエリの幅が大きい。

- [平方分割（雛形）](Sqrt_Decomposition_Template.hpp)

- [平方分割（例）](Sqrt_Decomposition_Example.hpp)（区間 chmin、区間 chmax、区間 add、区間 sum クエリを扱える）

## 平衡二分探索木

- [スプレー木](Splay_Tree.hpp)（スプレー操作を行うことで平衡を保つ二分探索木）

## Binary Trie

- [Binary Trie](Binary_Trie.hpp)（非負整数値を 2 進数表記することで Trie 木を構築する）

## ウェーブレット行列

静的な配列に対して、様々なクエリをオンラインで扱うことができる。

- [ウェーブレット行列](Wavelet_Matrix.hpp)
