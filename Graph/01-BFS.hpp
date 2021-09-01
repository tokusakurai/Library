
// 01-BFS(辺のコストが0か1のグラフにおける単一始点最短路)
// 計算量 O(E+V)

// 概要
// 始点から近い順に最短路を確定させる。
// dequeを用いる。
// コストが0の辺で最短路が更新されたらdequeの先頭に、コストが1の辺で更新されたらdequeの末尾に入れる。

// verified with
// https://atcoder.jp/contests/arc005/tasks/arc005_3

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
    const T INF_T;
    const int n;
    int m;

    vector<T> d;
    vector<int> pre_v;

    Weighted_Graph(int n) : es(n), INF_T(numeric_limits<T>::max() / 2), n(n), m(0), d(n), pre_v(n) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    T bfs(int s, int t = 0) {
        fill(begin(d), end(d), INF_T);
        deque<int> que;
        d[s] = 0, que.push_front(s);
        while (!que.empty()) {
            int i = que.front();
            que.pop_front();
            for (auto &e : es[i]) {
                if (d[i] + e.cost < d[e.to]) {
                    d[e.to] = d[i] + e.cost, pre_v[e.to] = i;
                    if (e.cost == 0)
                        que.push_front(e.to);
                    else
                        que.push_back(e.to);
                }
            }
        }
        return d[t];
    }

    vector<int> shortest_path(int s, int t) {
        if (bfs(s, t) == INF_T) return {};
        vector<int> ret;
        for (int now = t; now != s; now = pre_v[now]) ret.push_back(now);
        ret.push_back(s), reverse(begin(ret), end(ret));
        return ret;
    }
};
