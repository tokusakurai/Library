
// パスに対するオイラーツアー
// 計算量 O(n log(n))

// 概要
// 根付き木の頂点と辺を DFS で訪問した順 (戻るときに使った辺や頂点もカウントする) に並べる。
// 逆元が存在すれば、辺 (u,v) と辺 (v,u) が互いに打ち消し合うようにすることでパスクエリを区間クエリとすることができる。
// Segment Tree を用いて w = lca(u,v) を求めて、w-u パスと w-v パスに分けて扱う。

// verified with
// https://judge.yosupo.jp/problem/lca
// https://atcoder.jp/contests/abc294/tasks/abc294_g

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Algebraic-Structure/Monoid_Example.hpp"
#include "../Data-Structure/Segment_Tree.hpp"

template <bool directed = false>
struct Euler_Tour_Path {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> depth, id_v, vs; // 根から頂点 i までのパスに相当する区間は [0, id_v[i])
    vector<int> down, up;        // 辺 i の行き帰りに対応する番号
    Segment_Tree<Min_Monoid<int>> seg;
    const int n;
    int m;

    Euler_Tour_Path(int n) : es(n), depth(n), id_v(n), vs(2 * n - 1), seg(2 * n - 1, Min_Monoid<int>::id), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    void _dfs(int now, int pre, int &cnt_v, int &cnt_e) {
        id_v[now] = cnt_v, vs[cnt_v] = now;
        depth[now] = (pre == -1 ? 0 : depth[pre] + 1);
        seg.update(cnt_v++, depth[now]);
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            down[e.id] = cnt_e++;
            _dfs(e.to, now, cnt_v, cnt_e);
            up[e.id] = cnt_e++;
            vs[cnt_v] = now;
            seg.update(cnt_v++, depth[now]);
        }
    }

    void build(int root = 0) {
        down.resize(m), up.resize(m);
        int cnt_v = 0, cnt_e = 0;
        _dfs(root, -1, cnt_v, cnt_e);
    }

    // [0, id_v[u]) +  [0, id_v[v]) - [0, id_v[lca(u, v)]) * 2 のようにして使う
    int lca(int u, int v) const {
        if (id_v[u] > id_v[v]) swap(u, v);
        int d = seg.query(id_v[u], id_v[v] + 1);
        auto c = [d](int x) { return x <= d; };
        return vs[seg.find_first(id_v[u], c)];
    }
};
