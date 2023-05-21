
// Prim 法 (最小全域木)
// 計算量 O(m log(n))

// 概要
// ある頂点から始めて 1 つずつ辺を加えて木を構成する。
// 今木に含まれている頂点と木に含まれていない頂点を結ぶ辺のうち、もっともコストが小さいものを採用する。
// 昇順の priority_queue を用いる。
// 新たに木に加えた頂点と木に入っていない頂点を結ぶ辺を priority_queue に入れる。(この操作は合計で最大 m 回となる)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja

#pragma once
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
        using P = pair<T, int>;
        priority_queue<P, vector<P>, greater<P>> que;
        que.emplace(mincost[0] = zero_T, 0);
        T ret = zero_T;
        while (!que.empty()) {
            auto [p, i] = que.top();
            que.pop();
            if (used[i]) continue;
            used[i] = true, ret += p;
            for (auto &e : es[i]) {
                if (!used[e.to] && e.cost < mincost[e.to]) que.emplace(mincost[e.to] = e.cost, e.to);
            }
        }
        for (int i = 0; i < n; i++) {
            if (!used[i]) return INF_T;
        }
        return ret;
    }
};
