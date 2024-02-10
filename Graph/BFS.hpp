#pragma once

// BFS
// 計算量 O(n+m)

// 概要
// 始点から近い順に最短路を確定させる。
// queue を用いる。
// 辺のコストは全て 1 なので queue に入れるだけで始点から近い順が保たれる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C&lang=ja

#include <bits/stdc++.h>
using namespace std;

template <typename G>
struct BFS {
    vector<int> d;
    vector<int> pre_v, pre_e;
    const int s;

    BFS(const G &g, int s) : d(g.n, infty()), pre_v(g.n), pre_e(g.n), s(s) {
        queue<int> que;
        d[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            for (auto &e : g[i]) {
                if (d[i] + 1 < d[e.to]) {
                    d[e.to] = d[i] + 1;
                    pre_v[e.to] = i, pre_e[e.to] = e.id;
                    que.push(e.to);
                }
            }
        }
    }

    inline int infty() { return (1 << 30) - 1; }

    inline const int &operator[](int i) const { return d[i]; }

    // s-t 最短路の (頂点、辺)
    pair<vector<int>, vector<int>> shortest_path(int t) {
        if (d[t] == infty()) return make_pair(vector<int>{}, vector<int>{});
        vector<int> path_v, path_e;
        for (int now = t; now != s; now = pre_v[now]) {
            path_v.push_back(now);
            path_e.push_back(pre_e[now]);
        }
        path_v.push_back(s);
        reverse(begin(path_v), end(path_v));
        reverse(begin(path_e), end(path_e));
        return make_pair(path_v, path_e);
    }
};
