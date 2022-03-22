
// 01-BFS（辺のコストが 0 か 1 のグラフにおける単一始点最短路）
// 計算量 O(n+m)

// 概要
// 始点から近い順に最短路を確定させる。
// deque を用いる。
// コストが 0 の辺で最短路が更新されたら deque の先頭に、コストが 1 の辺で更新されたら deque の末尾に入れる。

// verified with
// https://atcoder.jp/contests/arc005/tasks/arc005_3

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct BFS_01 {
    struct edge {
        int to;
        int cost;
        int id;
        edge(int to, int cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> d;
    vector<int> pre_v, pre_e;
    const int INF_T = (1 << 30) - 1;
    const int n;
    int m;

    BFS_01(int n) : es(n), d(n), pre_v(n), pre_e(n), n(n), m(0) {}

    void add_edge(int from, int to, int cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    int shortest_path(int s, int t = 0) {
        fill(begin(d), end(d), INF_T);
        deque<int> que;
        d[s] = 0;
        que.push_front(s);
        while (!que.empty()) {
            int i = que.front();
            que.pop_front();
            for (auto &e : es[i]) {
                if (d[i] + e.cost < d[e.to]) {
                    d[e.to] = d[i] + e.cost;
                    pre_v[e.to] = i, pre_e[e.to] = e.id;
                    if (e.cost == 0) {
                        que.push_front(e.to);
                    } else {
                        que.push_back(e.to);
                    }
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
