
// BFS
// 計算量 O(n+m)

// 概要
// 始点から近い順に最短路を確定させる。
// queueを用いる。
// 辺のコストは全て1なのでqueueに入れるだけで始点から近い順が保たれる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Graph {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    const int n;
    int m;

    vector<int> d;
    vector<int> pre_v;

    Graph(int n) : es(n), n(n), m(0), d(n), pre_v(n) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    int bfs(int s, int t = 0) {
        fill(begin(d), end(d), INT_MAX / 2);
        queue<int> que;
        d[s] = 0, que.emplace(s);
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            for (auto &e : es[i]) {
                if (d[i] + 1 < d[e.to]) {
                    d[e.to] = d[i] + 1, pre_v[e.to] = i;
                    que.push(e.to);
                }
            }
        }
        return d[t];
    }

    vector<int> shortest_path(int s, int t) {
        if (bfs(s, t) == INT_MAX / 2) return {};
        vector<int> ret;
        for (int now = t; now != s; now = pre_v[now]) ret.push_back(now);
        ret.push_back(s), reverse(begin(ret), end(ret));
        return ret;
    }
};
