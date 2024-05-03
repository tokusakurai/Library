# 木

## 深さ優先探索 (DFS)

木上の任意の 2 点間の単純パスは一意に定まることから、DFS を用いて様々な操作を扱うことができる。

- [DFS (重みなし木)](DFS_Tree.hpp) (根からの距離・部分木のサイズ・直径・パス検出)

- [DFS (重み付き木)](DFS_Tree_Weighted.hpp) (根からの距離・部分木のサイズ・直径・パス検出)

## オイラーツアー

根付き木の頂点や辺を DFS で訪問した順に列として並べ、Segment Tree などのデータ構造と合わせて用いることで更新や求値クエリを高速に扱える。

- [オイラーツアー (部分木)](Euler-Tour_Subtree.hpp) (部分木に対するクエリを扱える)

- [オイラーツアー (パス)](Euler-Tour_Path.hpp) (逆向きの辺が打ち消されるようにすることで、LCA と組み合わせてパスに対するクエリを扱える)

## 最近共通祖先

根付き木の 2 点の共通の祖先で最も根から深いものをダブリンぐを用いて求めるアルゴリズム。

- [最近共通祖先 (重みなし木)](Lowest_Common_Ancestor.hpp)

- [最近共通祖先 (重み付き木)](Lowest_Common_Ancestor_Weighted.hpp)

## 全方位木 DP

全ての頂点についてのその頂点を根とした部分木 DP を効率的に扱うことができる。

- [全方位木 DP](Rerooting.hpp)

## 重心分解

木の重心 (取り除いたときに残る全ての部分木のサイズが元の木のサイズの半分以下となるような頂点) を取り除いて分割を繰り返すことで、効率的に分割統治を行うことができる。

- [重心分解](Centroid_Decomposition.hpp)

## Heavy-Light 分解

木をいくつかの列に分割し、単純パスをいくつかの列の一部区間をつなげたものとして表現することで効率的に最近共通祖先問題やパスクエリを扱うことができる。

- [Heavy-Light 分解](Heavy-Light_Decomposition.hpp)

- [Heavy-Light 分解 + データ構造](HLD_Data_Structure.hpp)

## Static Top Tree

木 DP の過程を深さ $\mathrm{O}(\log^2(n))$ の二分木で表現することで、頂点・辺に更新がある場合の DP 再計算を高速に行える。

- [Static Top Tree](Static_Top_Tree.hpp)

## 動的木

辺の追加・削除によって、木構造そのものが変化するときに効率的にパスクエリを扱うことができる。

- [Link-Cut Tree](Link_Cut_Tree.hpp) (パスをスプレー木で管理することで辺の追加・削除とパスクエリを扱える)

## Cartesian tree

数列を最小値で再帰的に分割することで得られる二分木。

- [Cartesian tree](Cartesian_Tree.hpp)

## 木上の最小シュタイナー木

頂点集合の追加・削除を行ったときの最小シュタイナー木のサイズを求めることができる。

- [木上の最小シュタイナー木](Dynamic_Steiner_Tree.hpp)

- [Auxiliary Tree](Auxiliary_Tree.hpp)  (最小シュタイナー木のパスを圧縮して得られる木を構築する)

## 根付き木の同型性判定

根付き木の各部分木を同型性に基づいて分類する。

- [根付き木の同型性判定](Rooted_Tree_Isomorphism.hpp)

## おまけ

- [木上のスケジューリング問題](Tree_Scheduling.hpp)
