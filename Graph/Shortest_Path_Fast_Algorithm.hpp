
// Shortest-Path-Fast-Algorithm（負辺があっても動作する単一始点最短路）
// 計算量 O(nm)

// 概要
// queue を用いる。
// 始点から始めて最短路が更新される点があれば queue に入れる。（既に入っていれば入れない）
// 負閉路が存在しない場合、各頂点について queue に入れられる回数は最大で V-1 回になる。（V 回入れられたら負閉路が存在する）

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
    vector<int> pre_v, pre_e;
    
    Weighted_Graph(int n) : es(n), d(n), n(n), m(0), pre_v(n), pre_e(n) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    T shortest_path_faster_algorithm(int s, int t = 0) {
        fill(begin(d), end(d), INF_T);
        queue<int> que;
        vector<bool> inque(n, false);
        vector<int> cnt(n, 0);
        d[s] = 0;
        que.emplace(s);
        inque[s] = true;
        cnt[s]++;
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            inque[i] = false;
            for (auto &e : es[i]) {
                if (d[i] + e.cost < d[e.to]) {
                    d[e.to] = d[i] + e.cost;
                    pre_v[e.to] = i, pre_e[e.to] = e.id;
                    if (!inque[e.to]) {
                        if (++cnt[e.to] >= n) return -INF_T; // s から到達できる負閉路あり
                        que.emplace(e.to);
                        inque[e.to] = true;
                    }
                }
            }
        }
        return d[t];
    }

    vector<int> shortest_path(int s, int t, bool use_id = true) {
        shortest_path_faster_algorithm(s);
        if (abs(d[t]) == INF_T) return {};
        vector<int> ret;
        for (int now = t; now != s; now = pre_v[now]) ret.push_back(use_id ? pre_e[now] : now);
        if (!use_id) ret.push_back(s);
        reverse(begin(ret), end(ret));
        return ret;
    }
};
