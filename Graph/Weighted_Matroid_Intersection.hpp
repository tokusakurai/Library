#pragma once

// 重み付きマトロイド交差
// 計算量 O(f(s+m^2 c)) (m = |E|、c は circuit クエリ 1 回の計算量、s は set クエリ 1 回の計算量、f は共通独立集合の元数の最大値)

// 概要
// マトロイド M_1 = (E,F_1)、M_2 = (E,F_2) と重み関数 w:E->R が与えられたとき、
// 各 k = 1,2,...,|E| について max{w(X) | X ∈ F_1 ∩ F_2, |X| = k} を求める。
// 補助グラフにおいて、Bellman-Ford 法を用いて最短路のうち通る辺数が最小のものを見つけ、更新を繰り返す。

// verified with
// https://codeforces.com/gym/103373/problem/I

#include <bits/stdc++.h>
using namespace std;

#include "../Graph/Bellman-Ford.hpp"

template <typename Matroid_1, typename Matroid_2, typename T>
vector<T> weighted_matroid_intersection(Matroid_1 M1, Matroid_2 M2, vector<T> w) {
    assert(M1.size() == M2.size());
    const int m = M1.size();
    for (int i = 0; i < m; i++) w[i] *= m + 1;
    vector<bool> X(m, false);
    vector<T> ret(m + 1, -1);
    ret[0] = 0;
    for (int i = 1; i <= m; i++) {
        M1.set(X), M2.set(X);
        Bellman_Ford<T, true> G(m + 2);
        int s = m, t = m + 1;
        for (int y = 0; y < m; y++) {
            if (X[y]) continue;
            vector<int> c1 = M1.circuit(y), c2 = M2.circuit(y);
            if (c1.empty()) G.add_edge(s, y, 0);
            for (auto &x : c1) {
                if (x != y) G.add_edge(x, y, w[x] + 1);
            }
            if (c2.empty()) G.add_edge(y, t, -w[y]);
            for (auto &x : c2) {
                if (x != y) G.add_edge(y, x, -w[y] + 1);
            }
        }
        G.shortest_path(s);
        vector<int> path = G.restore_path(s, t); // コスト最小のパスのうち通る辺数が最小のものを求める
        if (path.empty()) break;
        for (auto &e : path) {
            if (e != s && e != t) X[e] = !X[e];
        }
        T sum = 0;
        for (int j = 0; j < m; j++) {
            if (X[j]) sum += w[j];
        }
        ret[i] = sum / (m + 1);
    }
    return ret;
}
