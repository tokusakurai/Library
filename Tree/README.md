# 木

## 深さ優先探索(DFS)
木上の任意の2点間の単純パスは一意に定まることから、DFSを用いて様々な操作を扱うことができる。

- [DFS(重みなし木)](https://github.com/tokusakurai/Library/blob/main/Tree/DFS_Tree.hpp) (根からの距離・部分木のサイズ・直径・パス検出)

- [DFS(重み付き木)](https://github.com/tokusakurai/Library/blob/main/Tree/DFS_Tree_Weighted.hpp) (根からの距離・部分木のサイズ・直径・パス検出)

## オイラーツアー
根付き木の頂点や辺をDFSで訪問した順に列として並べ、セグメント木などのデータ構造と合わせて用いることで更新や求値クエリを高速に扱える。

- [オイラーツアー(頂点)](https://github.com/tokusakurai/Library/blob/main/Tree/Euler_Tour-1.hpp) (部分木に対するクエリを扱える)

- [オイラーツアー(辺)](https://github.com/tokusakurai/Library/blob/main/Tree/Euler_Tour-2.hpp) (逆向きの辺が打ち消されるようにすることでパスに対するクエリを扱える)

## 最近共通祖先
根付き木の2点の共通の祖先で最も根から深いものを求めるアルゴリズム。

- [最近共通祖先(重みなし木)](https://github.com/tokusakurai/Library/blob/main/Tree/Lowest_Common_Ancestor.hpp) (ダブリングを用いる)

- [最近共通祖先(重み付き木)](https://github.com/tokusakurai/Library/blob/main/Tree/Lowest_Common_Ancestor_Weighted.hpp)

## 全方位木DP
全ての頂点についてのその頂点を根とした部分木DPを効率的に扱うことができる。

- [全方位木DP](https://github.com/tokusakurai/Library/blob/main/Tree/Rerooting.hpp)

## 重心分解
木の重心(取り除いたときに残る全ての部分木のサイズが元の木のサイズの半分以下となるような頂点)を取り除いて分割を繰り返すことで、効率的に分割統治を行うことができる。

- [重心分解(雛形)](https://github.com/tokusakurai/Library/blob/main/Tree/Centroid_Template.hpp)

- [重心分解(例)](https://github.com/tokusakurai/Library/blob/main/Tree/Centroid_Example.hpp) (ある頂点からある距離の点の個数を求めるクエリを扱える)

## Heavy-Light分解
木をいくつかの列に分割し、単純パスをいくつかの列の一部区間をつなげたものとして表現することで効率的にパスクエリを扱うことができる。

- [Heavy-Light分解](https://github.com/tokusakurai/Library/blob/main/Tree/Heavy-Light_Decomposition.hpp)

## 動的木
辺の追加・削除によって、木構造そのものが変化するときに効率的にパスクエリを扱うことができる。

- [Link-Cut Tree](https://github.com/tokusakurai/Library/blob/main/Tree/Link_Cut_Tree.hpp) (パスをスプレー木で管理することで辺の追加・削除とパスクエリを扱える)

## Cartesian tree
数列を最小値で再帰的に分割することで得られる二分木。

- [Cartesian tree](https://github.com/tokusakurai/Library/blob/main/Tree/Cartesian_Tree.hpp)
