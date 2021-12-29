
// Dijkstra 法（負辺がないグラフにおける単一始点最短路）
// 計算量 O(n^2)

// 概要
// 始点から近い順に最短路を確定させる。
// ステップでまだ使われてない頂点で始点から最も近いものを調べる。

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, bool directed = false>
struct Table {
    vector<vector<T>> es;
    const T INF_T = numeric_limits<T>::max() / 2;
    const int n;

    vector<T> d;
    vector<int> pre_v;
    vector<bool> used;

    inline const vector<T> &operator[](int k) const { return es[k]; }

    inline vector<T> &operator[](int k) { return es[k]; }

    Table(int n) : es(n), n(n), d(n), pre_v(n), used(n) {
        for (int i = 0; i < n; i++) es[i].assign(n, INF_T);
        for (int i = 0; i < n; i++) es[i][i] = 0;
    }

    void add_edge(int from, int to, T cost = 1) {
        es[from][to] = min(es[from][to], cost);
        if (!directed) es[to][from] = min(es[to][from], cost);
    }

    T dijkstra(int s, int t = 0) {
        fill(begin(used), end(used), false), fill(begin(d), end(d), INF_T);
        d[s] = 0;
        for (int i = 0; i < n; i++) {
            int u = -1;
            for (int j = 0; j < n; j++) {
                if (!used[j] && (u == -1 || d[j] < d[u])) u = j;
            }
            used[u] = true;
            if (d[u] == INF_T) break;
            for (int j = 0; j < n; j++) {
                if (es[u][j] != INF_T) {
                    if (d[u] + es[u][j] < d[j]) d[j] = d[u] + es[u][j], pre_v[j] = u;
                }
            }
        }
        return d[t];
    }

    vector<int> shortest_path(int s, int t) {
        if (dijkstra(s, t) == INF_T) return {};
        vector<int> ret;
        for (int now = t; now != s; now = pre_v[now]) ret.push_back(now);
        ret.push_back(s), reverse(begin(ret), end(ret));
        return ret;
    }
};
