
// マトロイド交差
// 計算量 O(f(s+mc)) (m = |E|、c は circuit クエリ 1 回の計算量、s は set クエリ 1 回の計算量、f は共通独立集合の元数の最大値)

// 概要
// max{|X| | X ∈ F_1 ∩ F_2} を求める。
// 補助グラフにおいて、BFS で最短路を見つけ、更新を繰り返す。

// verified with
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Graph/Graph_Template.hpp"
#include "../Graph/BFS.hpp"

template <typename Matroid_1, typename Matroid_2>
pair<int, vector<int>> matroid_intersection(Matroid_1 M1, Matroid_2 M2) {
    assert(M1.size() == M2.size());
    const int m = M1.size();
    vector<bool> X(m, false);
    for (int i = 0;; i++) {
        M1.set(X), M2.set(X);
        Graph<true> G(m + 2);
        int s = m, t = m + 1;
        for (int y = 0; y < m; y++) {
            if (X[y]) continue;
            vector<int> c1 = M1.circuit(y), c2 = M2.circuit(y);
            if (c1.empty()) G.add_edge(s, y);
            for (auto &x : c1) {
                if (x != y) G.add_edge(x, y);
            }
            if (c2.empty()) G.add_edge(y, t);
            for (auto &x : c2) {
                if (x != y) G.add_edge(y, x);
            }
        }
        BFS B(G, s); // 最短路を求める
        vector<int> path = B.shortest_path(t).first;
        if (path.empty()) break;
        for (auto &e : path) {
            if (e != s && e != t) X[e] = !X[e];
        }
    }
    vector<int> ret;
    for (int i = 0; i < m; i++) {
        if (X[i]) ret.push_back(i);
    }
    return make_pair((int)ret.size(), ret);
};
