
// Dijkstra 法（負辺がないグラフにおける単一始点最短路）
// 計算量 O(n^2+m)

// 概要
// 始点から近い順に最短路を確定させる。
// ステップでまだ使われてない頂点で始点から最も近いものを調べる。

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, bool directed = false>
struct Dijkstra {
    struct edge {
        int to;
        T cost;
        int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    vector<T> d;
    vector<int> pre_v, pre_e;
    const T zero_T, INF_T;
    const int n;
    int m;

    Dijkstra(int n, T zero_T = 0, T INF_T = numeric_limits<T>::max() / 2) : es(n), d(n), pre_v(n), pre_e(n), zero_T(zero_T), INF_T(INF_T), n(n), m(0) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    T shortest_path(int s, int t = 0) {
        fill(begin(d), end(d), INF_T);
        vector<bool> used(n, false);
        d[s] = zero_T;
        for (int i = 0; i < n; i++) {
            int u = -1;
            for (int j = 0; j < n; j++) {
                if (!used[j] && (u == -1 || d[j] < d[u])) u = j;
            }
            used[u] = true;
            if (d[u] == INF_T) break;
            for (auto &e : es[u]) {
                if (d[u] + e.cost < d[e.to]) {
                    d[e.to] = d[u] + e.cost;
                    pre_v[e.to] = u, pre_e[e.to] = e.id;
                }
            }
        }
        return d[t];
    }

    vector<int> restore_path(int s, int t, bool use_id = false) {
        if (d[t] == INF_T) return {};
        vector<int> ret;
        for (int now = t; now != s; now = pre_v[now]) ret.push_back(use_id ? pre_e[now] : now);
        if (!use_id) ret.push_back(s);
        reverse(begin(ret), end(ret));
        return ret;
    }
};
