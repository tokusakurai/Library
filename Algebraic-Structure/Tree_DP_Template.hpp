#pragma once

// 木 DP テンプレート

#include <bits/stdc++.h>
using namespace std;

struct Tree_Root_1 {
    constexpr Tree_Root_1() {}
};

struct Tree_Rootless_1 {
    constexpr Tree_Rootless_1() {}
};

struct Path_1 {
    constexpr Path_1() {}
};

struct Point_1 {
    constexpr Point_1() {}
};

struct Vertex_1 {
    constexpr Vertex_1() {}
};

struct Edge_1 {
    constexpr Edge_1() {}
};

// 全方位木 DP 用
struct Tree_DP_1 {
    using Tree_Root = Tree_Root_1;         // 根あり木の型
    using Tree_Rootless = Tree_Rootless_1; // 根なし木の型
    using Vertex = Vertex_1;               // 頂点のデータ型
    using Edge = Edge_1;                   // 辺のデータ型

    // 根なし木と根なし木のマージ
    static Tree_Rootless merge(Tree_Rootless a, Tree_Rootless b) { return a; };

    // 根なし木に根を付けて根付き木にする
    static Tree_Root attach_root(Tree_Rootless a, Vertex b) {
        Tree_Root c;
        return c;
    };

    // 根付き木に辺を付けて根なし木にする
    static Tree_Rootless attach_edge(Tree_Root a, Edge b) {
        Tree_Rootless c;
        return c;
    };

    // merge, attach_root の単位元
    static const Tree_Rootless id;
};

const Tree_DP_1::Tree_Rootless Tree_DP_1::id = Tree_DP_1::Tree_Rootless();

// static top tree 用
struct Top_Tree_DP_1 {
    using Path_Cluster = Path_1;   // path cluster のデータ型
    using Point_Cluster = Point_1; // point cluster のデータ型
    using Vertex = Vertex_1;       // 頂点のデータ型
    using Edge = Edge_1;           // 辺のデータ型

    // (path cluster, path cluster) -> path cluster
    static Path_Cluster merge_path(Path_Cluster a, Path_Cluster b, Edge e) { return a; }

    // (point cluster, point cluster) -> point cluster
    static Point_Cluster merge_point(Point_Cluster a, Point_Cluster b) { return a; }

    // path cluster -> point cluster
    static Point_Cluster attach_edge(Path_Cluster a, Edge e) {
        Point_Cluster b;
        return b;
    }

    // point cluster -> path cluster
    static Path_Cluster attach_root(Point_Cluster a, Vertex v) {
        Path_Cluster b;
        return b;
    }

    // vertex -> path cluster
    static Path_Cluster singleton(Vertex v) { return Path_Cluster(); }
};
