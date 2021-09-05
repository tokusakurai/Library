# グラフ

## グラフの表現
グラフの表現の仕方として、主に隣接リスト、隣接行列、辺集合がある。

- [グラフ(雛形)](https://github.com/tokusakurai/Library/blob/main/Graph/Graph_Template.hpp)

## 深さ優先探索(DFS)
深さ優先探索。再帰関数を用いて簡潔に実装できる場合が多く、汎用性が非常に高い。

- [DFS(無向グラフ)](https://github.com/tokusakurai/Library/blob/main/Graph/DFS_Undirected.hpp) (パス検出・閉路検出)

- [DFS(有向グラフ)](https://github.com/tokusakurai/Library/blob/main/Graph/DFS_Directed.hpp) (パス検出・トポロジカルソート・閉路検出)

## 幅優先探索(BFS)
幅優先探索。辺のコストが全て等しいときの単一始点最短路を求めるのに利用される場合が多い。

- [BFS](https://github.com/tokusakurai/Library/blob/main/Graph/BFS.hpp) (単一始点最短路)

- [グリッド上のBFS](https://github.com/tokusakurai/Library/blob/main/Graph/Grid_BFS.hpp) (単一始点最短路)

- [01-BFS](https://github.com/tokusakurai/Library/blob/main/Graph/01-BFS.hpp) (辺のコストが0または1のときの単一始点最短路)

## 最短路問題
グラフの2点間の最短路(最短距離)を求めるアルゴリズム。

### 単一始点最短路(負辺なし)

- [Dijkstra法-1](https://github.com/tokusakurai/Library/blob/main/Graph/Dijkstra-1.hpp) (頂点数が小さい場合に高速に動作する)

- [Dijkstra法-2](https://github.com/tokusakurai/Library/blob/main/Graph/Dijkstra-2.hpp) (頂点数が大きい場合でも高速に動作する)

### 単一始点最短路(負辺あり)

- [Bellman-Ford法](https://github.com/tokusakurai/Library/blob/main/Graph/Bellman-Ford.hpp)

- [Shortest-Path-Faster-Algorithm](https://github.com/tokusakurai/Library/blob/main/Graph/Shortest_Path_Fast_Algorithm.hpp) (最悪計算量と比べて高速に動作することも多い)

### 全点対最短路

- [Warshall-Floyd法](https://github.com/tokusakurai/Library/blob/main/Graph/Warshall-Floyd.hpp) (負辺があってもよい)

## 最小全域木問題
辺のコストが全て非負のときに全域木を構成するための最小コストを求めるアルゴリズム。

- [Prim法-1](https://github.com/tokusakurai/Library/blob/main/Graph/Prim-1.hpp) (頂点数が小さい場合に高速に動作する)

- [Prim法-2](https://github.com/tokusakurai/Library/blob/main/Graph/Prim-2.hpp) (頂点数が大きい場合でも高速に動作する)

- [Kruscal法](https://github.com/tokusakurai/Library/blob/main/Graph/Kruscal.hpp)

- [Boruvka法](https://github.com/tokusakurai/Library/blob/main/Graph/Boruvka.hpp)

## ネットワークフロー
グラフ上のフローを扱うアルゴリズム。

### 最大流問題

- [Ford-Fulkerson法](https://github.com/tokusakurai/Library/blob/main/Graph/Ford-Fulkerson.hpp)

- [Dinic法](https://github.com/tokusakurai/Library/blob/main/Graph/Dinic.hpp) (最悪計算量と比べて非常に高速に動作することが多い)

### 最小費用流問題

- [Primal-Dual法-1](https://github.com/tokusakurai/Library/blob/main/Graph/Primal-Dual-1.hpp)

- [Primal-Dual法-2](https://github.com/tokusakurai/Library/blob/main/Graph/Primal-Dual-2.hpp) (ポテンシャルを用いた高速化)

### 2部グラフの最大マッチング

- [Hopcroft-Karp法](https://github.com/tokusakurai/Library/blob/main/Graph/Hopcroft-Karp.hpp)

## 強連結成分分解
有向グラフの各頂点が属する強連結成分(誘導部分グラフにおいて互いに行き来可能な点集合)を求めるアルゴリズム。

- [強連結成分分解](https://github.com/tokusakurai/Library/blob/main/Graph/Strongly-Connected_Components.hpp)

## 二重辺連結成分分解
無向グラフの各頂点が属する二重辺連結成分(誘導部分グラフが橋を含まないような点集合)を求めるアルゴリズム。

- [橋・関節点(Low-Link)](https://github.com/tokusakurai/Library/blob/main/Graph/Low_Link.hpp)

- [二重辺連結成分分解](https://github.com/tokusakurai/Library/blob/main/Graph/Two-Edge-Connencted_Components.hpp)

## その他発展的なアルゴリズム

- [オイラー路・オイラー閉路](https://github.com/tokusakurai/Library/blob/main/Graph/Eulerian_Trail.hpp) (全ての辺をちょうど一度通るパスや閉路を検出する)

- [彩色数](https://github.com/tokusakurai/Library/blob/main/Graph/Choromatic_Number.hpp) (隣接頂点の色が異なるように彩色するのに必要な最小の色の数を求める)

- [最大安定集合](https://github.com/tokusakurai/Library/blob/main/Graph/Maximum_Independent_Set.hpp) (どの2点も元のグラフで隣接しないような点集合でサイズが最大のものを求める)
