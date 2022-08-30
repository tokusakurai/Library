# 幾何

## 幾何ライブラリ

定数時間で行える基本的な幾何計算。

- [構造体](Structure.hpp) (点・直線 (線分)・円の構造体と基本的な演算)

- [直線の平行・垂直判定](Parallel_Orthogonal.hpp)

- [点から直線への垂線の足・点対称な点](Projection_Reflection.hpp)

- [図形の交差判定](Intersect.hpp)

- [図形の距離](Distance.hpp)

- [図形の交点](Crosspoint.hpp)

- [円と点の接線・円と円の共通接線](Tangent.hpp)

- [垂直二等分線・アポロニウスの円](Apollonius.hpp) (2 点からの距離の比が一定になる点の軌跡)

## アルゴリズム

多数の点を処理するアルゴリズム。

- [多角形](Polygon.hpp) (面積と内外判定)

- [凸包](Convex_Hull.hpp) (元の点集合を含む最小の凸多角形を構築する)

- [最近点対](Closest_Pair.hpp)

## All

上記を全て 1 つにまとめたもの。

- [All](All.hpp)

## 整数幾何

全ての点の座標が整数のときに、整数計算のみで扱える幾何。

- [凸包](Convex_Hull_Integer.hpp)

- [最近点対](Closest_Pair_Integer.hpp)

- [偏角ソート](Sort_Arg.hpp)
