# グラフ

## グラフの表現
グラフの表現の仕方として、主に隣接リスト、隣接行列、辺集合がある。

- [グラフ(雛形)](https://github.com/tokusakurai/graph/blob/main/Graph_Template.cpp)

## 深さ優先探索(DFS)
再帰関数を用いて簡潔に実装できる場合が多いため、汎用性が非常に高い。

- [DFS(無向グラフ)](https://github.com/tokusakurai/graph/blob/main/Undirected_Graph_DFS.cpp) (パス検出・閉路検出)

- [DFS(有向グラフ)](https://github.com/tokusakurai/graph/blob/main/Directed_Graph_DFS.cpp) (パス検出・トポロジカルソート・閉路検出)

## 幅優先探索(BFS)
辺のコストが全て等しいときの単一始点最短路を求めるのに利用される場合が多い。

- [BFS](https://github.com/tokusakurai/graph/blob/main/BFS.cpp) (単一始点最短路)

- [グリッド上のBFS](https://github.com/tokusakurai/graph/blob/main/Grid_BFS.cpp) (単一始点最短路)

辺のコストが0または1であるとき、dequeなどの先頭と末尾の挿入・削除が扱えるデータ構造を用いれば高速にBFSを回すことができる。

- [01-BFS](https://github.com/tokusakurai/graph/blob/main/01-BFS.cpp) (辺のコストが0または1のときの単一始点最短路)

## 最短路問題
グラフの2点間の最短路(最短距離)を求めるアルゴリズム。

### 単一始点最短路(負辺なし)

- [Dijkstra法-1](https://github.com/tokusakurai/graph/blob/main/Dijkstra-1.cpp) (頂点数が小さい場合に高速に動作する)

- [Dijkstra法-2](https://github.com/tokusakurai/graph/blob/main/Dijkstra-2.cpp) (頂点数が大きい場合でも高速に動作する)

### 単一始点最短路(負辺あり)

- [Bellman-Ford法](https://github.com/tokusakurai/graph/blob/main/Bellman-Ford.cpp)

- [Shortest-Path-Faster-Algorithm](https://github.com/tokusakurai/graph/blob/main/SPFA.cpp) (最悪計算量と比べて高速に動作することも多い)

### 全点対最短路

- [Warshall-Floyd法](https://github.com/tokusakurai/graph/blob/main/Warshall-Floyd.cpp) (負辺があってもよい)

## 最小全域木問題
辺のコストが全て非負のときに全域木を構成するための最小コストを求めるアルゴリズム。負辺が存在する場合は、それらを全て採用してから同様の手順を行えば良い。

- [Prim法-1](https://github.com/tokusakurai/graph/blob/main/Prim-1.cpp) (頂点数が小さい場合に高速に動作する)

- [Prim法-2](https://github.com/tokusakurai/graph/blob/main/Prim-2.cpp) (頂点数が大きい場合でも高速に動作する)

- [Kruscal法](https://github.com/tokusakurai/graph/blob/main/Kruscal.cpp)

- [Boruvka法](https://github.com/tokusakurai/graph/blob/main/Boruvka.cpp)

## 最大流問題
始点と終点との間におけるフローの最大流量を求めるアルゴリズム。

- [Ford-Fulkerson法](https://github.com/tokusakurai/graph/blob/main/Ford_Fulkerson.cpp) (最悪計算量と比べて高速に動作することも多い)

- [Dinic法](https://github.com/tokusakurai/graph/blob/main/Dinic.cpp) (最悪計算量と比べて高速に動作することも多い)

## 最小費用流問題
始点と終点との間におけるある流量のフローの最小コストを求めるアルゴリズム。

- [Primal-Dual法-1](https://github.com/tokusakurai/graph/blob/main/Primal-Dual-1.cpp)

- [Primal-Dual法-2](https://github.com/tokusakurai/graph/blob/main/Primal-Dual-2.cpp) (ポテンシャルを用いた高速化)

## 2部グラフの最大マッチング
2部グラフにおける最大マッチングを構成するアルゴリズム。

- [Hopcroft-Karp法](https://github.com/tokusakurai/graph/blob/main/Hopcroft_Karp.cpp) (最大流と比べて最悪計算量が小さい)

## 強連結成分分解
有向グラフの強連結成分(誘導部分グラフにおいて互いに行き来可能な点集合)を1つにまとめるアルゴリズム。

- [強連結成分分解](https://github.com/tokusakurai/graph/blob/main/SCC.cpp)

## 二重辺連結成分分解
無向グラフの二重辺連結成分(誘導部分グラフが橋を含まないような点集合)を1つにまとめるアルゴリズム。橋・関節点を高速に列挙するアルゴリズムを用いて高速に行うことができる。

- [橋・関節点(Low-Link)](https://github.com/tokusakurai/graph/blob/main/Low_Link.cpp)

- [二重辺連結成分分解](https://github.com/tokusakurai/graph/blob/main/TECC.cpp)

## その他発展的なアルゴリズム

- [オイラー路・オイラー閉路](https://github.com/tokusakurai/graph/blob/main/Eulerian_Trail.cpp) (全ての辺をちょうど一度通るパスや閉路を検出する)

- [彩色数](https://github.com/tokusakurai/graph/blob/main/Choromatic_Number.cpp) (隣接頂点の色が異なるように彩色するのに必要な最小の色の数を求める)

- [最大安定集合](https://github.com/tokusakurai/graph/blob/main/Maximum_Independent_Set.cpp) (どの2点も元のグラフで隣接しないような点集合でサイズが最大のものを求める)
