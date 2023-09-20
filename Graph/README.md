# グラフ

## グラフの表現

グラフの表現の仕方として、主に隣接リスト、隣接行列、辺集合がある。

- [グラフ（雛形）](Graph_Template.hpp)

## 深さ優先探索 (DFS)

深さ優先探索。再帰関数を用いて簡潔に実装できる場合が多く、汎用性が非常に高い。

- [DFS（無向グラフ）](DFS_Undirected.hpp)（パス検出・閉路検出）

- [DFS（有向グラフ）](DFS_Directed.hpp)（パス検出・トポロジカルソート・閉路検出）

## 幅優先探索 (BFS)

幅優先探索。辺のコストが全て 1 のときの単一始点最短路を求めるのに使われる。

- [BFS](BFS.hpp)（辺のコストが全て 1 のときの単一始点最短路）

- [01-BFS](01-BFS.hpp)（辺のコストが 0 または 1 のときの単一始点最短路）

## ハミルトンサイクル

- [ハミルトンサイクル](Hamilton_Cycle.hpp)（ハミルトンサイクルを持つ部分集合の列挙、部分集合におけるハミルトンサイクルの復元）

## 最短路問題

グラフの 2 点間の最短路（最短距離）を求めるアルゴリズム。

### 単一始点最短路（負辺なし）

- [Dijkstra 法 1](Dijkstra-1.hpp)（疎グラフに対して高速に動作する）

- [Dijkstra 法 2](Dijkstra-2.hpp)（密グラフに対して高速に動作する）

### 単一始点最短路（負辺あり）

- [Bellman-Ford 法](Bellman-Ford.hpp)

- [Shortest-Path-Faster-Algorithm](Shortest-Path-Faster-Algorithm.hpp)（最悪計算量と比べて高速に動作することも多い）

### 全点対最短路

- [Warshall-Floyd 法](Warshall-Floyd.hpp)（負辺があってもよい）

## 最小全域木問題

辺のコストが全て非負のときに全域木を構成するための最小コストを求めるアルゴリズム。

- [Prim 法 1](Prim-1.hpp)（疎グラフに対して高速に動作する）

- [Prim 法 2](Prim-2.hpp)（密グラフに対して高速に動作する）

- [Kruscal 法](Kruscal.hpp)

- [Boruvka 法](Boruvka.hpp)

- [Manhattan 最小全域木](Manhattan_MST.hpp)（辺重みが Manhattan 距離で与えられる完全グラフの MST）

## ネットワークフロー

グラフ上のフローを扱うアルゴリズム。

### 最大流問題

- [Ford-Fulkerson 法](Ford-Fulkerson.hpp)

- [Dinic 法](Dinic.hpp)（最悪計算量と比べて非常に高速に動作することが多い）

### 最小費用流問題

- [Primal-Dual 法 1](Primal-Dual-1.hpp)

- [Primal-Dual 法 2](Primal-Dual-2.hpp)（ポテンシャルを用いた高速化、疎グラフに対して高速に動作する）

- [Primal-Dual 法 3](Primal-Dual-3.hpp)（密グラフに対して高速に動作する）

### 最大マッチング

- [Hopcroft-Karp 法](Hopcroft-Karp.hpp) (二部グラフの最大マッチング)

- [Edmonds の花アルゴリズム](Edmonds_Blossom.hpp) (一般グラフの最大マッチング)

### 割り当て問題

最小重み最大マッチングを求めるアルゴリズム。最小費用流問題の特殊ケースとなっている。

- [Hungarian 法](Hungarian.hpp)

## 強連結成分分解

有向グラフの各頂点が属する強連結成分(誘導部分グラフにおいて互いに行き来可能な点集合)を求めるアルゴリズム。

- [強連結成分分解](Strongly-Connected_Components.hpp)

## 橋・関節点

無効グラフの橋・関節点を列挙するアルゴリズム。関連として、二重辺連結成分分解・二重連結成分分解がある。

- [橋・関節点 (Low-Link)](Low_Link.hpp)

- [二重辺連結成分分解](Two-Edge-Connected_Components.hpp)（橋を含まないような連結成分に分解する）

- [二重連結成分分解](Biconnected_Components.hpp)（関節点を含まないような連結成分に分解する）

## DM 分解

二部グラフの隣接行列の行と列を並び替えてできるだけ細かくブロック三角化するアルゴリズム。

- [DM 分解](Dulmage-Mendelsohn_Decomposition.hpp)

## マトロイド

マトロイドとはある公理系を満たす集合システムのことであり、多くの組み合わせ最適化問題をマトロイドを用いて表現することができる。

- [マトロイド](Matroid.hpp)

- [マトロイド交差](Matroid_Intersection.hpp)

- [重み付きマトロイド交差](Weighted_Matroid_Intersection.hpp)

## その他

- [オイラー路・オイラー閉路](Eulerian_Trail.hpp)（全ての辺をちょうど一度通るパスや閉路を検出する）

- [彩色数](Choromatic_Number.hpp)（隣接頂点の色が異なるように彩色するのに必要な最小の色の数を求める）

- [最大安定集合](Maximum_Independent_Set.hpp)（どの 2 点も元のグラフで隣接しないような点集合でサイズが最大のものを求める）

- [三角形列挙](Triangle_Enumerate.hpp)（グラフの長さ 3 のサイクルを列挙する）
