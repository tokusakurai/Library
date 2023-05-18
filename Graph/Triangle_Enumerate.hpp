
// 無向グラフの長さ 3 の閉路列挙
// 計算量 O(n+m√m)

// 概要
// グラフの各頂点を次数が小さい順にソートする。
// 各辺を、上のソートで前のものから後ろのものへの向きに向きづけした有向グラフを考えると各頂点の次数は √(2m) 以下になる。
// 各辺 {i,j} を固定して、{i,k},{j,k} が存在するような k を、i,j から出る辺を全て見ることによって列挙できる。

// verified with
// https://judge.yosupo.jp/problem/enumerate_triangles

#pragma once
using namespace std;
#include <bits/stdc++.h>

struct Triangle_Enumerate {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    const int n;
    int m;

    Triangle_Enumerate(int n) : es(n), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        es[to].emplace_back(from, m);
        m++;
    }

    void enumerate(const function<void(int, int, int)> &f, bool use_edge = false) {
        auto comp = [&](int i, int j) {
            if (es[i].size() != es[j].size()) return es[i].size() < es[j].size();
            return i < j;
        };

        vector<vector<edge>> g(n);
        for (int i = 0; i < n; i++) {
            for (auto &e : es[i]) {
                if (comp(i, e.to)) g[i].push_back(e);
            }
        }
        vector<int> used(n, -1);
        for (int i = 0; i < n; i++) {
            for (auto &e3 : g[i]) used[e3.to] = e3.id;
            for (auto &e1 : g[i]) {
                for (auto &e2 : g[e1.to]) {
                    if (used[e2.to] != -1) use_edge ? f(e1.id, e2.id, used[e2.to]) : f(i, e1.to, e2.to);
                }
            }
            for (auto &e3 : g[i]) used[e3.to] = -1;
        }
    }
};
