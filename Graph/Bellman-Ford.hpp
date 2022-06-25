
// Bellman-Ford 法（負辺があっても動作する単一始点最短路）
// 計算量 O(nm)

// 概要
// 各ステップで全ての辺を用いて最短距離を更新する。
// 負の閉路がなければステップ回数は n-1 回行えばよい。（n 回目のステップでも更新が発生したら負閉路が存在する）

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, bool directed = false>
struct Bellman_Ford {
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

    Bellman_Ford(int n, T zero_T = 0, T INF_T = numeric_limits<T>::max() / 2) : es(n), d(n), pre_v(n), pre_e(n), zero_T(zero_T), INF_T(INF_T), n(n), m(0) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    T shortest_path(int s, int t = 0) { // 到達不可能なら INF、コストをいくらでも小さくできるなら -INF
        fill(begin(d), end(d), INF_T);
        d[s] = zero_T;
        for (int i = 0; i < 2 * n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[j] == INF_T) continue;
                for (auto &e : es[j]) {
                    if (d[j] + e.cost < d[e.to]) {
                        d[e.to] = d[j] + e.cost;
                        pre_v[e.to] = j, pre_e[e.to] = e.id;
                        if (i >= n - 1) d[e.to] = -INF_T;
                    }
                }
            }
        }
        return d[t];
    }

    bool negative_loop() { // 全ての負閉路を検出
        fill(begin(d), end(d), zero_T);
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

    vector<int> restore_path(int s, int t, bool use_id = false) {
        if (abs(d[t]) == INF_T) return {};
        vector<int> ret;
        for (int now = t; now != s; now = pre_v[now]) ret.push_back(use_id ? pre_e[now] : now);
        if (!use_id) ret.push_back(s);
        reverse(begin(ret), end(ret));
        return ret;
    }
};
