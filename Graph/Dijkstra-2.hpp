
// Dijkstra法（負辺がないグラフにおける単一始点最短路）
// 計算量 O(m log(n))

// 概要
// 始点から近い順に最短路を確定させる。
// 昇順の priority_queue を用いる。
// 最短距離が更新されたときに priority_queue に入れる。（この操作は合計で最大 m 回となる）

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja
// https://judge.yosupo.jp/problem/shortest_path

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, bool directed = false>
struct Weighted_Graph {
    struct edge {
        int to;
        T cost;
        int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    const T INF_T = numeric_limits<T>::max() / 2;
    const int n;
    int m;

    vector<T> d;
    vector<int> pre_v, pre_e;

    Weighted_Graph(int n) : es(n), n(n), m(0), d(n), pre_v(n), pre_e(n) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    T dijkstra(int s, int t = 0) {
        fill(begin(d), end(d), INF_T);
        using P = pair<T, int>;
        priority_queue<P, vector<P>, greater<P>> que;
        que.emplace(d[s] = 0, s);
        while (!que.empty()) {
            auto [p, i] = que.top();
            que.pop();
            if (p > d[i]) continue;
            for (auto &e : es[i]) {
                if (d[i] + e.cost < d[e.to]) {
                    pre_v[e.to] = i, pre_e[e.to] = e.id;
                    que.emplace(d[e.to] = d[i] + e.cost, e.to);
                }
            }
        }
        return d[t];
    }

    vector<int> shortest_path(int s, int t, bool use_id = false) {
        if (dijkstra(s, t) == INF_T) return {};
        vector<int> ret;
        for (int now = t; now != s; now = pre_v[now]) ret.push_back(use_id ? pre_e[now] : now);
        if (!use_id) ret.push_back(s);
        reverse(begin(ret), end(ret));
        return ret;
    }
};
