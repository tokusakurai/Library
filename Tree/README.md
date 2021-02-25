# 木

## 深さ優先探索(DFS)
木上の任意の2点間の単純パスは一意に定まることから、DFSを用いて様々な操作を扱うことができる。

- [DFS(重みなし木)](https://github.com/tokusakurai/Library/blob/main/Tree/Tree-DFS-1.cpp) (根からの距離・部分木のサイズ・直径・パス検出)

- [DFS(重み付き木)](https://github.com/tokusakurai/Library/blob/main/Tree/Tree-DFS-2.cpp) (根からの距離・部分木のサイズ・直径・パス検出)

## オイラーツアー
根付き木の頂点や辺をDFSで訪問した順に列として並べ、セグメント木などのデータ構造と合わせて用いることで更新や求値クエリを高速に扱える。

- [オイラーツアー(頂点)](https://github.com/tokusakurai/Library/blob/main/Tree/Euler_Tour-1.cpp) (部分木に対するクエリを扱える)

- [オイラーツアー(辺)](https://github.com/tokusakurai/Library/blob/main/Tree/Euler_Tour-2.cpp) (逆向きの辺が打ち消されるようにすることでパスに対するクエリを扱える)

## 最近共通祖先
根付き木の2点の共通の祖先で最も深いものを高速に求めるアルゴリズム。

- [最近共通祖先](https://github.com/tokusakurai/Library/blob/main/Tree/LCA.cpp) (ダブリングを用いる)

## 重心分解
木の重心(取り除いたときに残る全ての部分木のサイズが元の木のサイズの半分以下となるような頂点)を取り除くことによって分解を繰り返すことで、効率的に分割統治を行うことができる。

- [重心分解(雛形)](https://github.com/tokusakurai/Library/blob/main/Tree/Centroid_Template.cpp)

- [重心分解(例)](https://github.com/tokusakurai/Library/blob/main/Tree/Centroid_Example.cpp) (ある頂点からある距離の点の個数を求めるクエリを扱える)

## Heavy-Light分解
木をうまく列に分解することでパスを少ない個数の列の区間をつなげたものとして表現し、効率的にパスクエリを扱うことができる。

- [Heavy-Light分解](https://github.com/tokusakurai/Library/blob/main/Tree/HLD.cpp)
