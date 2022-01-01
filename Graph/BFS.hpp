
// BFS
// 計算量 O(n+m)

// 概要
// 始点から近い順に最短路を確定させる。
// queue を用いる。
// 辺のコストは全て 1 なので queue に入れるだけで始点から近い順が保たれる。

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
    vector<int> pre_v, pre_e;

    Graph(int n) : es(n), n(n), m(0), d(n), pre_v(n), pre_e(n) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    int bfs(int s, int t = 0) {
        fill(begin(d), end(d), -1);
        queue<int> que;
        d[s] = 0;
        que.emplace(s);
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            for (auto &e : es[i]) {
                if (d[e.to] == -1) {
                    d[e.to] = d[i] + 1;
                    pre_v[e.to] = i, pre_e[e.to] = e.id;
                    que.push(e.to);
                }
            }
        }
        return d[t];
    }

    vector<int> shortest_path(int s, int t, bool use_id = false) {
        if (bfs(s, t) == -1) return {};
        vector<int> ret;
        for (int now = t; now != s; now = pre_v[now]) ret.push_back(use_id ? pre_e[now] : now);
        if (!use_id) ret.push_back(s);
        reverse(begin(ret), end(ret));
        return ret;
    }
};
