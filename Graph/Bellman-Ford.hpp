#pragma once

// Bellman-Ford 法 (負辺があっても動作する単一始点最短路)
// 計算量 O(nm)

// 概要
// 各ステップで全ての辺を用いて最短距離を更新する。
// 負の閉路がなければステップ回数は n-1 回行えばよい。(n 回目のステップでも更新が発生したら負閉路が存在する)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja

#include <bits/stdc++.h>
using namespace std;

template <typename G>
struct Bellman_Ford {
    using L = typename G::L;

    vector<L> d;
    vector<int> pre_v, pre_e;
    const int s;

    Bellman_Ford(const G &g, int s) : d(g.n, infty()), pre_v(g.n, -1), pre_e(g.n, -1), s(s) {
        d[s] = zero();
        for (int i = 0; i < 2 * g.n; i++) {
            for (int j = 0; j < g.n; j++) {
                if (d[j] == infty()) continue;
                for (auto &e : g[j]) {
                    L nd = (d[j] == -infty() ? -infty() : d[j] + e.get_len());
                    if (nd < d[e.to]) {
                        d[e.to] = nd;
                        pre_v[e.to] = j, pre_e[e.to] = e.id;
                        if (i >= g.n - 1) d[e.to] = -infty();
                    }
                }
            }
        }
    }

    inline L infty() { return (L(1) << ((sizeof(L) >> 1) * 15)) - 1; }

    inline L zero() { return L(0); }

    inline const L &operator[](int i) const { return d[i]; }

    // s-t 最短路の (頂点、辺)
    pair<vector<int>, vector<int>> shortest_path(int t) {
        if (d[t] == infty()) return make_pair(vector<int>{}, vector<int>{});
        vector<int> path_v, path_e;
        for (int now = t; now != s; now = pre_v[now]) {
            path_v.push_back(now);
            path_e.push_back(pre_e[now]);
        }
        path_v.push_back(s);
        reverse(begin(path_v), end(path_v));
        reverse(begin(path_e), end(path_e));
        return make_pair(path_v, path_e);
    }
};

// グラフ全体に負閉路があるか
template <typename G>
bool negative_cycle(const G &g) {
    using L = typename G::L;
    vector<L> d(g.n, 0);
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            for (auto &e : g[j]) {
                if (d[j] + e.get_len() < d[e.to]) {
                    d[e.to] = d[j] + e.get_len();
                    if (i == g.n - 1) return true;
                }
            }
        }
    }
    return false;
}
