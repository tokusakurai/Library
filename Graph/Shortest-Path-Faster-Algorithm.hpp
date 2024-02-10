#pragma once

// Shortest-Path-Faster-Algorithm (負辺があっても動作する単一始点最短路)
// 計算量 O(nm)

// 概要
// queue を用いる。
// 始点から始めて最短路が更新される点があれば queue に入れる。(既に入っていれば入れない)
// 負閉路が存在しない場合、各頂点について queue に入れられる回数は最大で V-1 回になる。(V 回入れられたら負閉路が存在する)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja

#include <bits/stdc++.h>
using namespace std;

template <typename G>
struct Shortest_Path_Faster_Algorithm {
    using L = typename G::L;

    vector<L> d;
    vector<int> pre_v, pre_e;
    const int s;

    Shortest_Path_Faster_Algorithm(const G &g, int s) : d(g.n, infty()), pre_v(g.n, -1), pre_e(g.n, -1), s(s) {
        queue<int> que;
        vector<bool> inque(g.n, false);
        vector<int> cnt(g.n, 0);
        d[s] = zero();
        que.push(s);
        inque[s] = true;
        cnt[s]++;
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            inque[i] = false;
            for (auto &e : g[i]) {
                L nd = (d[i] == -infty() ? -infty() : d[i] + e.get_len());
                if (nd < d[e.to]) {
                    d[e.to] = nd;
                    pre_v[e.to] = i, pre_e[e.to] = e.id;
                    if (!inque[e.to]) {
                        if (++cnt[e.to] >= g.n) d[e.to] = -infty();
                        que.push(e.to);
                        inque[e.to] = true;
                    }
                }
            }
        }
    }

    inline L infty() { return (L(1) << ((sizeof(L) >> 1) * 15)) - 1; }

    inline L zero() { return L(0); }

    inline const L &operator[](int i) const { return d[i]; }

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
