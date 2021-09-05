
// Bellman-Ford法(負辺があっても動作する単一始点最短路)
// 計算量 O(E*V)

// 概要
// 各ステップで全ての辺を用いて最短距離を更新する。
// 負の閉路がなければステップ回数はV-1回行えばよい。(V回目のステップでも更新が発生したら負閉路が存在する)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja

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
    vector<int> pre_v;

    Weighted_Graph(int n) : es(n), n(n), m(0), d(n), pre_v(n) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    bool bellman_ford(int s) { // sから到達可能な負閉路を検出
        fill(begin(d), end(d), INF_T);
        d[s] = 0;
        bool ret = false;
        for (int i = 0; i < 2 * n; i++) {
            for (int j = 0; j < n; j++) {
                for (auto &e : es[j]) {
                    if (d[j] == INF_T) continue;
                    if (d[j] + e.cost < d[e.to]) {
                        d[e.to] = d[j] + e.cost, pre_v[e.to] = j;
                        if (i >= n - 1) d[e.to] = -INF_T, ret = true;
                    }
                }
            }
        }
        return ret;
    }

    bool negative_loop() { // 全ての負閉路を検出
        fill(begin(d), end(d), 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (auto &e : es[j]) {
                    if (d[j] + e.cost < d[e.to]) {
                        d[e.to] = d[j] + e.cost;
                        if (i == n - 1) return true;
                    }
                }
            }
        }
    }

    vector<int> shortest_path(int s, int t) {
        if (abs(bellman_ford(s, t)) == INF_T) return {};
        vector<int> ret;
        for (int now = t; now != s; now = pre_v[now]) ret.push_back(now);
        ret.push_back(s), reverse(begin(ret), end(ret));
        return ret;
    }
};
