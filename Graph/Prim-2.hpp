#pragma once

// Prim 法 (最小全域木)
// 計算量 O(n^2+m)

// 概要
// ある頂点から始めて1つずつ辺を加えて木を構成する。
// 今木に含まれている頂点と木に含まれていない頂点を結ぶ辺のうち、もっともコストが小さいものを採用する。
// 各ステップで、木に含まれていない頂点を全てチェックする。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Prim {
    struct edge {
        int to;
        T cost;
        int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    const T zero_T, INF_T;
    const int n;
    int m;

    Prim(int n, T zero_T = 0, T INF_T = numeric_limits<T>::max() / 2) : es(n), zero_T(zero_T), INF_T(INF_T), n(n), m(0) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        es[to].emplace_back(from, cost, m);
        m++;
    }

    T min_spanning_tree() {
        vector<T> mincost(n, INF_T);
        vector<bool> used(n, false);
        mincost[0] = zero_T;
        T ret = zero_T;
        for (int i = 0; i < n; i++) {
            int u = -1;
            for (int j = 0; j < n; j++) {
                if (used[j]) continue;
                if (u == -1 || mincost[j] < mincost[u]) u = j;
            }
            if (mincost[u] == INF_T) continue;
            used[u] = true;
            ret += mincost[u];
            for (auto &e : es[u]) mincost[e.to] = min(mincost[e.to], e.cost);
        }
        for (int i = 0; i < n; i++) {
            if (!used[i]) return INF_T;
        }
        return ret;
    }
};
