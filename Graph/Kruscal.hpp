#pragma once

// Kruscal 法 (最小全域木)
// 計算量 O(n α(n)+m log(m))

// 概要
// 辺をコストの昇順にソートする。
// Union-Find 木を用いる。
// 上から辺を見ていって、両端が別の連結成分に属していればその辺を採用し、そうでなければ棄却する。

// verified with
// https://judge.yosupo.jp/problem/minimum_spanning_tree
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp

#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Union_Find_Tree.hpp"

template <typename G>
struct Kruscal {
    using L = typename G::L;
    vector<pair<int, int>> mst;
    vector<int> mst_id;
    L weight;

    Kruscal(const G &g) : weight(0) {
        vector<tuple<L, int, int, int>> edges;
        for (int i = 0; i < g.n; i++) {
            for (auto e : g[i]) {
                if (i < e.to) edges.emplace_back(e.get_len(), i, e.to, e.id);
            }
        }
        sort(begin(edges), end(edges));
        Union_Find_Tree uf(g.n);
        for (auto [w, u, v, id] : edges) {
            if (uf.unite(u, v)) {
                weight += w;
                mst.emplace_back(u, v);
                mst_id.push_back(id);
            }
        }
    }
};
