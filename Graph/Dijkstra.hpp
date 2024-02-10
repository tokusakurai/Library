#pragma once

// Dijkstra 法 (負辺がないグラフにおける単一始点最短路)
// 計算量 O(m log(n))

// 概要
// 始点から近い順に最短路を確定させる。
// 昇順の priority_queue を用いる。
// 最短距離が更新されたときに priority_queue に入れる。 (この操作は合計で最大 m 回となる)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja
// https://judge.yosupo.jp/problem/shortest_path

#include <bits/stdc++.h>
using namespace std;

template <typename G>
struct Dijkstra {
    using L = typename G::L;

    vector<L> d;
    vector<int> pre_v, pre_e;
    const int s;

    Dijkstra(const G &g, int s, bool dense = false) : d(g.n, infty()), pre_v(g.n, -1), pre_e(g.n, -1), s(s) {
        if (!dense) {
            using P = pair<L, int>;
            priority_queue<P, vector<P>, greater<P>> que;
            que.emplace(d[s] = zero(), s);
            while (!que.empty()) {
                auto [p, i] = que.top();
                que.pop();
                if (p > d[i]) continue;
                for (auto &e : g[i]) {
                    if (d[i] + e.get_len() < d[e.to]) {
                        pre_v[e.to] = i, pre_e[e.to] = e.id;
                        que.emplace(d[e.to] = d[i] + e.get_len(), e.to);
                    }
                }
            }
        } else {
            vector<bool> used(g.n, false);
            d[s] = zero();
            for (int i = 0; i < g.n; i++) {
                int u = -1;
                for (int j = 0; j < g.n; j++) {
                    if (!used[j] && (u == -1 || d[j] < d[u])) u = j;
                }
                used[u] = true;
                if (d[u] == infty()) break;
                for (auto &e : g[u]) {
                    if (d[u] + e.get_len() < d[e.to]) {
                        d[e.to] = d[u] + e.get_len();
                        pre_v[e.to] = u, pre_e[e.to] = e.id;
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
