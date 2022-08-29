
// パスに対するオイラーツアー
// 計算量 O(n log(n))

// 概要
// 根付き木の頂点と辺を DFS で訪問した順 (戻るときに使った辺や頂点もカウントする) に並べる。
// 逆元が存在すれば、辺 (u,v) と辺 (v,u) が互いに打ち消し合うようにすることでパスクエリを区間クエリとすることができる。
// Segment Tree を用いて w = lca(u,v) を求めて、w-u パスと w-v パスに分けて扱う。

// verified with
// https://judge.yosupo.jp/problem/lca
// https://atcoder.jp/contests/abc014/tasks/abc014_4

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Segment_Tree.hpp"

template <bool directed = false>
struct Euler_Tour_Path {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> depth, p;
    vector<int> l, r; // 辺 i は l[i] 回目と r[i] 回目に通る。
    using P = pair<int, int>;
    const function<P(P, P)> f = [](const P &a, const P &b) { return min(a, b); };
    Segment_Tree<P> seg;
    const int n;
    int m;

    Euler_Tour_Path(int n) : es(n), depth(n), p(n), seg(2 * n - 1, {n, -1}, f, {n, -1}), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    void _dfs(int now, int pre, int &cnt1, int &cnt2) {
        p[now] = cnt1++;
        depth[now] = (pre == -1 ? 0 : depth[pre] + 1);
        seg.change(p[now], {depth[now], now});
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            l[e.id] = cnt2++;
            _dfs(e.to, now, cnt1, cnt2);
            r[e.id] = cnt2++;
            seg.change(cnt1++, {depth[now], now});
        }
    }

    void build(int root = 0) {
        l.resize(m), r.resize(m);
        int cnt1 = 0, cnt2 = 0;
        _dfs(root, -1, cnt1, cnt2);
    }

    // w = lca(u,v) とすると、u-v パスは [p[w],p[u]) と [p[w],p[v]) を合算したものになる。
    int lca(int u, int v) const {
        if (p[u] > p[v]) swap(u, v);
        return seg.query(p[u], p[v] + 1).second;
    }
};
