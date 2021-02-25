# データ構造

## Union-Find木
2つの集合を統合して1つにすること(Union)と、ある要素が属する集合を求めること(Find)が高速にできる。

- [Union-Find木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Union_Find_Tree.cpp)

- [重み付きUnion-Find木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Weighted_Union_Find_Tree.cpp) (各頂点に重みを与えたとき、weight(y)-weight(x) = wの制約を扱える)

- [部分永続Union-Find木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Partitially_Persistent_Union_Find_Tree.cpp) (各Union操作に時刻を与えたとき、任意の時刻でのFindクエリを扱える)

- [Undo可能Union-Find木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Undo_Union_Find_Tree.cpp) (Union操作を巻き戻すことができる)

## Binary-Indexed木
配列に対して1点加算と区間和取得が高速にできる。セグメント木と比べてメモリが軽い、定数倍が速いというメリットがある。

- [Binary-Indexed木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Binary_Indexed_Tree.cpp)

## セグメント木
配列に対して1点更新と区間演算が高速にできる。ただし、演算はモノイドとしての性質を満たさなければならない。

- [セグメント木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Segment_Tree.cpp)

遅延評価(求値クエリが来るまで値の更新を保留すること)を用いることによって区間更新を扱うこともできる。

- [双対セグメント木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Dual_Segment_Tree.cpp) (作用素の演算がモノイドの性質を満たすとき、区間更新と1点取得を扱える)

- [遅延評価付きセグメント木](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Lazy_Segment_Tree.cpp) (上記2つを組み合わせることで区間更新と区間演算を扱える)

## スパーステーブル
配列が不変であり演算が結合則と冪等性を満たすとき、区間演算が高速にできる。セグメント木と比べて区間演算を高速に扱えるが、メモリ消費が大きいことと扱える演算の幅が小さくなることに注意。

- [スパーステーブル](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Sparse_Table.cpp)

## 平方分割
配列を適当なサイズごとのバケットに分割することで、区間クエリを行ったときに、全体にクエリがかかる区間と一部のみにクエリがかかる区間に分かれることを利用した高速化。セグメント木と比べて計算量は落ちるが、扱えるクエリの幅が大きい。

- [平方分割(雛形)](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Sqrt_Decomposition_Template.cpp)

- [平方分割(例)](https://github.com/tokusakurai/Library/blob/main/Data-Structure/Sqrt_Decomposition_Example.cpp) (区間chmin、区間chmax、区間add、区間sumクエリを扱える)
